#include "MemoryManager.h"
#include <iostream>

namespace Framework
{
    MemoryManager::MemoryManager(Process* process) : m_process(process)
    {
    }

    uintptr_t MemoryManager::ResolvePointerChain(uintptr_t offset, const OffsetList& offsets)
    {
        for (size_t i = 0; i < offsets.size(); i++) {
            if (!Read(offset, offset)) {
                std::cerr << "Failed to resolve pointer at step " << i << std::endl;
                return 0;
            }
            offset += offsets[i];
        }

        return offset;
    }

    std::vector<PatternByte> MemoryManager::ParsePattern(const std::string& pattern) {
        std::vector<PatternByte> bytes;
        std::string byteStr;

        for (size_t i = 0; i < pattern.length(); i++) {
            if (pattern[i] == ' ') {
                continue;
            }

            byteStr += pattern[i];
            i++;

            if (i < pattern.length() && pattern[i] != ' ') {
                byteStr += pattern[i];
            }

            PatternByte pb{};
            if (byteStr == "??") {
                pb.isWildcard = true;
            }
            else {
                pb.value = static_cast<BYTE>(std::stoi(byteStr, nullptr, 16));
                pb.isWildcard = false;
            }
            bytes.push_back(pb);
            byteStr.clear();
        }

        return bytes;
    }

    uintptr_t MemoryManager::FindPattern(HANDLE hProcess, const std::vector<PatternByte>& pattern) {
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);

        uintptr_t startAddress = reinterpret_cast<uintptr_t>(sysInfo.lpMinimumApplicationAddress);
        uintptr_t endAddress = reinterpret_cast<uintptr_t>(sysInfo.lpMaximumApplicationAddress);

        MEMORY_BASIC_INFORMATION mbi{};
        std::vector<BYTE> buffer;

        while (startAddress < endAddress) {
            if (VirtualQueryEx(hProcess, reinterpret_cast<LPCVOID>(startAddress), &mbi, sizeof(mbi))) {
                if (mbi.State == MEM_COMMIT &&
                    (mbi.Protect == PAGE_READWRITE || mbi.Protect == PAGE_READONLY || mbi.Protect == PAGE_EXECUTE_READ)) {

                    buffer.resize(mbi.RegionSize);
                    SIZE_T bytesRead;

                    if (ReadProcessMemory(hProcess, mbi.BaseAddress, buffer.data(), mbi.RegionSize, &bytesRead)) {
                        if (mbi.RegionSize > 100 * 1024 * 1024) { 
                            startAddress += mbi.RegionSize;
                            continue;
                        }
                        for (size_t i = 0; i < bytesRead - pattern.size(); i++) {
                            bool found = true;

                            for (size_t j = 0; j < pattern.size(); j++) {
                                if (!pattern[j].isWildcard && buffer[i + j] != pattern[j].value) {
                                    found = false;
                                    break;
                                }
                            }

                            if (found) {
                                std::cout << "Found pattern @ 0x" << std::hex << reinterpret_cast<uintptr_t>(mbi.BaseAddress) + i << std::dec << std::endl;
                                return reinterpret_cast<uintptr_t>(mbi.BaseAddress) + i;
                            }
                        }
                    }
                }
                startAddress += mbi.RegionSize;
            }
            else {
                break;
            }
        }
        return 0;
    }
}
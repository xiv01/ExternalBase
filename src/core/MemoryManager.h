#pragma once

#include "Process.h"
#include "../common/Types.h"
#include <vector>

namespace Framework
{
    class MemoryManager
    {
    private:
        Process* m_process;

    public:
        explicit MemoryManager(Process* process);

        template<typename T>
        bool Read(uintptr_t address, T& value);

        template<typename T>
        bool Write(uintptr_t address, const T& value);

        uintptr_t ResolvePointerChain(uintptr_t offset, const OffsetList& offsets);
		std::vector<PatternByte> ParsePattern(const std::string& pattern);
        uintptr_t FindPattern(HANDLE hProcess, const std::vector<PatternByte>& pattern);
    };

    template<typename T>
    bool MemoryManager::Read(uintptr_t address, T& value)
    {
        return ReadProcessMemory(m_process->GetHandle(), (LPCVOID)address, &value, sizeof(T), nullptr);
    }

    template<typename T>
    bool MemoryManager::Write(uintptr_t address, const T& value)
    {
        return WriteProcessMemory(m_process->GetHandle(), (LPVOID)address, &value, sizeof(T), nullptr);
    }
}

#include "Process.h"
#include <tlhelp32.h>
#include <iostream>

namespace Framework
{
    Process::Process() : m_processId(0), m_processHandle(NULL)
    {
    }

    Process::~Process()
    {
        if (m_processHandle != NULL) {
            CloseHandle(m_processHandle);
        }
    }

    bool Process::Attach(const std::wstring& processName)
    {
        m_processId = GetProcessId(processName);
        if (m_processId == 0) {
            std::cerr << "Failed to find process: " << std::string(processName.begin(), processName.end()) << std::endl;
            return false;
        }

        m_processHandle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, m_processId);
        if (m_processHandle == NULL) {
            std::cerr << "Failed to open process. Error: " << GetLastError() << std::endl;
            return false;
        }

        std::cout << "Successfully attached to process ID: " << m_processId << std::endl;
        return true;
    }

    HANDLE Process::GetHandle() const
    {
        return m_processHandle;
    }

    DWORD Process::GetId() const
    {
        return m_processId;
    }

    DWORD Process::GetProcessId(const std::wstring& processName)
    {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 procEntry;
            procEntry.dwSize = sizeof(procEntry);

            if (Process32First(hSnap, &procEntry)) {
                do {
                    if (!_wcsicmp(procEntry.szExeFile, processName.c_str())) {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(hSnap, &procEntry));
            }
            CloseHandle(hSnap);
        }
        return procId;
    }

    uintptr_t Process::FindModuleBaseAddress(DWORD processId, const std::wstring& moduleName)
    {
        uintptr_t modBaseAddr = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);

            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!_wcsicmp(modEntry.szModule, moduleName.c_str())) {
                        modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                        break;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
            CloseHandle(hSnap);
        }
        return modBaseAddr;
    }
}
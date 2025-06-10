#pragma once

#include <windows.h>
#include <string>
#include <map>

namespace Framework
{
    class Process
    {
    private:
        DWORD m_processId;
        uintptr_t m_moduleBaseAddress;
        HANDLE m_processHandle;

    public:
        Process();
        ~Process();

        bool Attach(const std::wstring& processName);
        HANDLE GetHandle() const;
        DWORD GetId() const;

    private:
        DWORD GetProcessId(const std::wstring& processName);
        uintptr_t FindModuleBaseAddress(DWORD processId, const std::wstring& moduleName);
    };
}

#pragma once

#include "../core/Process.h"
#include "../core/MemoryManager.h"
#include "../core/GUI.h"
#include "../common/Types.h"

namespace Framework
{
    class Cheat
    {
    private:
        Process m_process;
        MemoryManager m_memoryManager;
        GUI m_gui;

        const std::wstring PROCESS_NAME = L"";

        const std::vector<AddressOffset> m_addressOffsets = {
            {
                "NAME",
                "PATTERN",
                {0x1, 0x2, 0x3}
            }
        };

        std::map<std::string, uintptr_t> m_addresses;

    public:
        Cheat();
        bool Initialize();
        void Run();
    };
}

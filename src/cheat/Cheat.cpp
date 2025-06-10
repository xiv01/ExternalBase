#include "Cheat.h"
#include "../features/TemplateFeature.h"
#include "../common/Constants.h"
#include <iostream>
#include <memory>

namespace Framework
{
    Cheat::Cheat() : m_memoryManager(&m_process)
    {
    }

    bool Cheat::Initialize()
    {
        std::cout << "Initializing " << Constants::WINDOW_TITLE << std::endl;
        if (!m_process.Attach(PROCESS_NAME)) {
            std::cerr << "Failed to attach to the game process" << std::endl;
            return false;
        }

        std::cout << "Scanning for patterns ..." << std::endl;

        for (const auto& addressOffset : m_addressOffsets) {
            uintptr_t baseAddr = m_memoryManager.FindPattern(
                m_process.GetHandle(),
                m_memoryManager.ParsePattern(addressOffset.basePattern)
            );

            if (baseAddr == 0) {
                std::cerr << "Failed to find pattern for " << addressOffset.name << std::endl;
                return false;
            }

            uintptr_t resolvedAddr = m_memoryManager.ResolvePointerChain(baseAddr, addressOffset.offsets);
            if (resolvedAddr == 0) {
                std::cerr << "Failed to resolve pointer chain for " << addressOffset.name << std::endl;
                return false;
            }

            m_addresses[addressOffset.name] = resolvedAddr;
            std::cout << addressOffset.name << " address: 0x" << std::hex << resolvedAddr << std::dec << std::endl;
        }

        std::cout << "Initializing GUI" << std::endl;
        if (!m_gui.Initialize()) {
            std::cerr << "Failed to initialize GUI" << std::endl;
            return false;
        }

        return true;
    }

    void Cheat::Run()
    {
        m_gui.Run();
        std::cout << "Cheat closed successfully" << std::endl;
    }
}
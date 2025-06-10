#pragma once

#include "../core/MemoryManager.h"

namespace Framework
{
    class TemplateStruct
    {
    private:
        MemoryManager* m_memory;
        uintptr_t m_baseAddress;

    public:
        TemplateStruct(MemoryManager* memory, uintptr_t baseAddress);
        ~TemplateStruct() = default;

        bool GetIsAlive() const;
        void SetIsAlive(bool enabled);

        uintptr_t GetBaseAddress() const;

        static constexpr uint32_t ISALIVE = 0x100;
    };
}

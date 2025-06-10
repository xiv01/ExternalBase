#include "TemplateStruct.h"

namespace Framework
{
    TemplateStruct::TemplateStruct(MemoryManager* memory, uintptr_t baseAddress)
        : m_memory(memory), m_baseAddress(baseAddress)
    {
    }

    bool TemplateStruct::GetIsAlive() const
    {
        bool value = false;
        m_memory->Read(m_baseAddress + ISALIVE, value);
        return value;
    }

    void TemplateStruct::SetIsAlive(bool enabled)
    {
        m_memory->Write(m_baseAddress + ISALIVE, enabled);
    }

    uintptr_t TemplateStruct::GetBaseAddress() const
    {
        return m_baseAddress;
    }
}
#include "CheatFeature.h"

namespace Framework
{
    CheatFeature::CheatFeature(const std::string& name, MemoryManager* memory)
        : m_name(name), m_enabled(false), m_memory(memory)
    {
    }

    const std::string& CheatFeature::GetName() const
    {
        return m_name;
    }

    bool CheatFeature::IsEnabled() const
    {
        return m_enabled;
    }

    void CheatFeature::SetEnabled(bool enabled)
    {
        m_enabled = enabled;
    }
}
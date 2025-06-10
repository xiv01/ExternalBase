#pragma once

#include "MemoryManager.h"
#include <string>

namespace Framework
{
    class CheatFeature
    {
    protected:
        std::string m_name;
        bool m_enabled;
        MemoryManager* m_memory;

    public:
        CheatFeature(const std::string& name, MemoryManager* memory);
        virtual ~CheatFeature() = default;

        virtual void OnGUI() = 0;
        virtual void OnUpdate() = 0;

        const std::string& GetName() const;
        bool IsEnabled() const;
        void SetEnabled(bool enabled);
    };
}

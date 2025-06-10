#pragma once

#include "../core/CheatFeature.h"

namespace Framework
{
    class TemplateFeature : public CheatFeature
    {
    private:
        uintptr_t m_address;
        float m_value;
        bool m_toggle;

    public:
        TemplateFeature(MemoryManager* memory, uintptr_t moneyAddress);
        void OnGUI() override;
        void OnUpdate() override;
    };
}

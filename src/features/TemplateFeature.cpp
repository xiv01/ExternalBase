#include "TemplateFeature.h"
#include <iostream>
#include <imgui.h>

namespace Framework
{
    TemplateFeature::TemplateFeature(MemoryManager* memory, uintptr_t address)
        : CheatFeature("Money Cheat", memory),
        m_address(address),
        m_value(1000.0f),
        m_toggle(false)
    {
        m_memory->Read(m_address, m_value);
        std::cout << "Money Address: 0x" << std::hex << (m_address) << std::dec << " | Value: " << m_value << std::endl;
    }

    void TemplateFeature::OnGUI()
    {
        ImGui::Text("Test");
        ImGui::PushItemWidth(200);
        if (ImGui::Button("test button")) {
            m_memory->Write(m_address, m_value);
            std::cout << "test button pressed" << std::endl;
        }

        ImGui::Checkbox("Test Toggle", &m_toggle);
    }

    void TemplateFeature::OnUpdate()
    {
        if (m_toggle) {
            m_memory->Write(m_address, m_value);
            std::cout << "test checkbox toggled" << std::endl;
        }
    }
}
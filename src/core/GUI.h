#pragma once

#include "CheatFeature.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <vector>
#include <memory>

namespace Framework
{
    class GUI
    {
    private:
        GLFWwindow* m_window;
        ImGuiIO* m_io;
        std::vector<std::unique_ptr<CheatFeature>> m_features;

    public:
        GUI();
        ~GUI();

        bool Initialize();
        void AddFeature(std::unique_ptr<CheatFeature> feature);
        void Run();
    };
}

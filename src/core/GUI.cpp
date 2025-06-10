#include "GUI.h"
#include "../common/Constants.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

namespace Framework
{
    GUI::GUI() : m_window(nullptr), m_io(nullptr)
    {
    }

    GUI::~GUI()
    {
        if (m_window) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            glfwDestroyWindow(m_window);
            glfwTerminate();
        }
    }

    bool GUI::Initialize()
    {
        if (!glfwInit()) {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(
            Constants::WINDOW_WIDTH,
            Constants::WINDOW_HEIGHT,
            Constants::WINDOW_TITLE,
            NULL, NULL
        );

        if (!m_window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }

        glfwSetWindowAttrib(m_window, GLFW_FLOATING, GLFW_TRUE);
        glfwSetWindowOpacity(m_window, 0.9f);
        glfwMakeContextCurrent(m_window);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        m_io = &io;
        io.Fonts->AddFontFromFileTTF(Constants::FONT_PATH, Constants::FONT_SIZE);

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        ImGui::StyleColorsDark();

        return true;
    }

    void GUI::AddFeature(std::unique_ptr<CheatFeature> feature)
    {
        m_features.push_back(std::move(feature));
    }

    void GUI::Run()
    {
        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));

            ImGui::Begin(Constants::WINDOW_TITLE, nullptr,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoTitleBar);

            float yPos = 20.0f;
            for (auto& feature : m_features) {
                ImGui::SetCursorPos(ImVec2(15, yPos));
                feature->OnGUI();
                yPos += 80.0f;
            }

            ImGui::End();

            for (auto& feature : m_features) {
                feature->OnUpdate();
            }

            ImGui::Render();
            int w, h;
            glfwGetFramebufferSize(m_window, &w, &h);
            glViewport(0, 0, w, h);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(m_window);
        }
    }
}
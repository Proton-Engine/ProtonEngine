/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/ui/ui_context.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ProtonEngine::Ui
{

UiContext::UiContext(GLFWwindow * window)
{
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

UiContext::~UiContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

} // namespace ProtonEngine::Ui
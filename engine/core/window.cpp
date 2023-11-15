/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "window.h"
#include "backends/imgui_impl_opengl3.h"
#include "event_bus.h"

#include "protonengine/core/logger.h"
#include "protonengine/renderer/renderer.h"

#include <backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <fmt/core.h>

namespace ProtonEngine::Core
{

Window::Window(int32_t width, int32_t height, std::string_view title)
{
    PROTON_LOG_INFO(fmt::format("Creating window of size {}x{} with title {}", width, height, title));
    if (!glfwInit())
    {
        const char * description;
        glfwGetError(&description);
        PROTON_LOG_ERROR(fmt::format("Failed to initialize glfw with error: {}", description));
        exit(EXIT_FAILURE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_windowHandle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(m_windowHandle);

    Renderer::setWindowContext([](const char * proc_name) { return (void *)glfwGetProcAddress(proc_name); });

    initializeImGui();
    registerCallbacks();

    EventBus::fireEvent(Event::WINDOW_RESIZE_EVENT, WindowResizeEventContext{width, height});
}

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_windowHandle);
}

auto Window::update() noexcept -> bool
{
    if (glfwWindowShouldClose(m_windowHandle) ||
        glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE))
    {
        glfwTerminate();
        return false;
    }

    glfwSwapBuffers(m_windowHandle);
    glfwPollEvents();
    return true;
}

void Window::initializeImGui() const
{
    ImGui::CreateContext();
    ImGuiIO & io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(m_windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Window::registerCallbacks() const
{
    glfwSetKeyCallback(m_windowHandle, [](GLFWwindow * /*window*/, int key, int /*scancode*/, int action, int /*mods*/) {
        if (action == GLFW_REPEAT)
            return;

        KeyEventEventContext context{
            .key = static_cast<Key>(key),
            .state = action == GLFW_PRESS ? KeyState::PRESSED : KeyState::RELEASED};
        EventBus::fireEvent(Event::KEY_EVENT, context);
    });

    glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow *, const int newWidth, const int newHeight) {
        EventBus::fireEvent(Event::WINDOW_RESIZE_EVENT, WindowResizeEventContext{newWidth, newHeight});
    });
}

} // namespace ProtonEngine::Core
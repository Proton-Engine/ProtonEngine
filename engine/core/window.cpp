/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "window.h"
#include "event_bus.h"
#include "input.h"

#include "protonengine/renderer/renderer.h"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <fmt/core.h>

namespace ProtonEngine::Core {

Window::Window(int32_t width, int32_t height, std::string_view title)
{
    if (!glfwInit())
    {
        const char * description;
        glfwGetError(&description);
        fmt::print("Failed to initialize glfw with error: {}\n", description);
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

    EventBus::fireEvent(Event::WINDOW_RESIZE_EVENT, WindowResizeEventContext{width, height});
}

Window::~Window()
{
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

} // namespace ProtonEngine::Core
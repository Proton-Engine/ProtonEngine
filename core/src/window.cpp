/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/window.h"
#include "protonengine/renderer/renderer.h"

#include <fmt/core.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

namespace ProtonEngine::Core
{

Window::Window(int32_t width, int32_t height, std::string_view title)
{
    if(!glfwInit())
    {
        const char *description;
        glfwGetError(&description);
        fmt::print("Failed to initialize glfw with error: {}\n", description);
        exit(EXIT_FAILURE);
    }

    m_windowHandle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    glfwMakeContextCurrent(m_windowHandle);

    Renderer::setWindowContext(glfwGetProcAddress);
}

Window::~Window()
{
    glfwDestroyWindow(m_windowHandle);
}

void Window::update()
{
    Renderer::update();

    glfwSwapBuffers(m_windowHandle);

    if (glfwWindowShouldClose(m_windowHandle) ||
        glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE))
    {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    glfwWaitEvents();
}

} // namespace ProtonEngine::Core
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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
    if (glfwWindowShouldClose(m_windowHandle) ||
        glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE))
    {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    glfwSwapBuffers(m_windowHandle);
    glfwPollEvents();
}

} // namespace ProtonEngine::Core
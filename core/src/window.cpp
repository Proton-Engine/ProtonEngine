/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/window.h"

#include <fmt/core.h>

#include "OpenGL/gl.h"
//#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ProtonEngine::Core
{

Window::Window(int32_t width, int32_t height, std::string_view title)
{
    if(!glfwInit())
    {
        const char *description;
        glfwGetError(&description);
        fmt::print("Error: {}", description);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_windowHandle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
}

Window::~Window()
{
    glfwDestroyWindow(m_windowHandle);
}

void Window::update()
{
    glfwMakeContextCurrent(m_windowHandle);
    glfwSwapBuffers(m_windowHandle);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    if (glfwWindowShouldClose(m_windowHandle) ||
        glfwGetKey(m_windowHandle, GLFW_KEY_ESCAPE))
    {
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }

    glfwWaitEvents();
}

} // namespace ProtonEngine::Core
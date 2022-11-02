/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/window.h"
#include "fmt/core.h"

#include <glad/gl.h>
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

    int version = gladLoadGL(glfwGetProcAddress);
    if(version == 0)
    {
        exit(EXIT_FAILURE);
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_windowHandle);
}

void Window::update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();


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
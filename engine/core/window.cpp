/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "window.h"
#include "input.h"

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
    
    Renderer::setWindowContext([](const char * proc_name){return (void *) glfwGetProcAddress(proc_name);});

    glfwSetKeyCallback(m_windowHandle, Input::onKeyBoardEvent);
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
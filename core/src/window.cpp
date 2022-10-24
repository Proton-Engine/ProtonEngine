/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/window.h"

#include <fmt/core.h>
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

//    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    m_windowHandle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
}

Window::~Window()
{
    glfwDestroyWindow(m_windowHandle);
}

} // namespace ProtonEngine::Core
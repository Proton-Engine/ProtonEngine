/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <cinttypes>
#include <string_view>

extern struct GLFWwindow;

namespace ProtonEngine::Core
{

class Window
{
public:
    Window(int32_t width, int32_t height, std::string_view title);
    ~Window();

private:
    GLFWwindow * m_windowHandle{};
};

} // namespace ProtonEngine::Core
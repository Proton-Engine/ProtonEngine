/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <cinttypes>
#include <string_view>

struct GLFWwindow;

namespace ProtonEngine::Core
{

class Window
{
public:
    Window(int32_t width, int32_t height, std::string_view title);
    ~Window();

    [[nodiscard]] auto update() noexcept -> bool;

private:
    GLFWwindow * m_windowHandle{};

    void initializeImGui() const;
    void registerCallbacks() const;
};

} // namespace ProtonEngine::Core
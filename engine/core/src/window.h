/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/renderer.h"
#include "protonengine/ui/ui_context.h"

#include <memory>
#include <string_view>

struct GLFWwindow;

namespace ProtonEngine::Core
{

class Window
{
public:
    Window(int32_t width, int32_t height, std::string_view title, Renderer::Renderer & renderer);
    ~Window();

    [[nodiscard]] auto update() noexcept -> bool;
    void setVSync(bool enabled) noexcept;

private:
    GLFWwindow * m_windowHandle{};
    std::unique_ptr<Ui::UiContext> m_uiContext;

    void registerCallbacks() const;
};

} // namespace ProtonEngine::Core
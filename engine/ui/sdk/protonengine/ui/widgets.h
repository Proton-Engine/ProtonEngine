/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/itexture.h"


#include <format>
#include <glm/vec2.hpp>
#include <string>
#include <string_view>

namespace ProtonEngine::Ui
{

namespace Widgets
{

template <class... Args>
void Text(std::format_string<Args...> fmt, Args &&... args)
{
    Text(std::format(fmt, std::forward<Args>(args)...));
}

[[nodiscard]] auto getWindowSize() -> glm::i32vec2;

void Text(const std::string & text);
void Image(const Renderer::ITexture & texture, glm::i32vec2);

[[nodiscard]] auto BeginMenuBar() -> bool;
void EndMenuBar();

[[nodiscard]] auto BeginMainMenuBar() -> bool;
void EndMainMenuBar();

[[nodiscard]] auto BeginMenu(const std::string & label) -> bool;
void EndMenu();

[[nodiscard]] auto MenuItem(const std::string & label) -> bool;

void Separator();

} // namespace Widgets

} // namespace ProtonEngine::Ui

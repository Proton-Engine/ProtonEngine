/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "../sdk/protonengine/ui/widgets.h"

#include <imgui.h>

namespace ProtonEngine::Ui
{

namespace Widgets
{

auto getWindowSize() -> glm::i32vec2
{
    const auto [x, y] = ImGui::GetContentRegionAvail();
    return glm::i32vec2(x, y);
}

void Text(const std::string & text)
{
    ImGui::TextUnformatted(text.data());
}

void Image(const Renderer::ITexture & texture, glm::i32vec2 size)
{
    ImGui::Image((ImTextureID)(intptr_t)texture.id(), ImVec2(size.x, size.y));
}

[[nodiscard]] auto BeginMenuBar() -> bool
{
    return ImGui::BeginMenuBar();
}

void EndMenuBar()
{
    ImGui::EndMenuBar();
}

[[nodiscard]] auto BeginMainMenuBar() -> bool
{
    return ImGui::BeginMainMenuBar();
}

void EndMainMenuBar()
{
    ImGui::EndMainMenuBar();
}

[[nodiscard]] auto BeginMenu(const std::string & label) -> bool
{
    return ImGui::BeginMenu(label.c_str());
}

void EndMenu()
{
    ImGui::EndMenu();
}

[[nodiscard]] auto MenuItem(const std::string & label) -> bool
{
    return ImGui::MenuItem(label.c_str());
}

void Separator()
{
    ImGui::Separator();
}

} // namespace Widgets

} // namespace ProtonEngine::Ui
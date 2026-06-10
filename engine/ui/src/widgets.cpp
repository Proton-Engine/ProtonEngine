// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "protonengine/ui/widgets.h"

#include <imgui.h>

namespace ProtonEngine::Ui
{

namespace Widgets
{

void Text(const std::string & text)
{
    ImGui::TextUnformatted(text.data());
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
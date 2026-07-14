// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "menu_bar.h"

#include <../../../engine/ui/sdk/protonengine/ui/widgets.h>

namespace ProtonEditor::Layers
{

MenuBar::MenuBar() : Layer("Menu bar")
{
}

void MenuBar::onAttach()
{
}

void MenuBar::onImGuiRender()
{
    if (ProtonEngine::Ui::Widgets::BeginMainMenuBar())
    {
        if (ProtonEngine::Ui::Widgets::BeginMenu("File"))
        {
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("New project");
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Open project");
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Close project");

            ProtonEngine::Ui::Widgets::Separator();

            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Save");
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Settings");
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Close");

            ProtonEngine::Ui::Widgets::EndMenu();
        }

        if (ProtonEngine::Ui::Widgets::BeginMenu("Build"))
        {
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Build");
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Run");

            ProtonEngine::Ui::Widgets::EndMenu();
        }

        if (ProtonEngine::Ui::Widgets::BeginMenu("Entity"))
        {
            std::ignore = ProtonEngine::Ui::Widgets::MenuItem("Add empty");
            ProtonEngine::Ui::Widgets::EndMenu();
        }

        ProtonEngine::Ui::Widgets::EndMainMenuBar();
    }
}

void MenuBar::onUpdate(float timeStep)
{
}


} // namespace ProtonEditor::Layers

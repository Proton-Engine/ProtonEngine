// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "properties.h"

#include "../../../engine/ui/sdk/protonengine/ui/widgets.h"

namespace ProtonEditor::Layers
{

Properties::Properties() : Layer("Properties")
{
}

void Properties::onAttach()
{
}

void Properties::onImGuiRender()
{
    ProtonEngine::Ui::Widgets::Text("No project loaded");
}

void Properties::onUpdate(float timeStep)
{
}

} // namespace ProtonEditor::Layers
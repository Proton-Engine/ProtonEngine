// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "scene_hierarchy.h"

#include "protonengine/ui/widgets.h"

namespace ProtonEditor::Layers
{

SceneHierarchyLayer::SceneHierarchyLayer() : Layer("Scene hierarchy")
{
}

void SceneHierarchyLayer::onAttach()
{
}

void SceneHierarchyLayer::onImGuiRender()
{
    ProtonEngine::Ui::Widgets::Text("No project loaded");
}

void SceneHierarchyLayer::onUpdate(float timeStep)
{
}

} // namespace ProtonEditor::Layers
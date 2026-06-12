/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "editor_view.h"

#include "protonengine/ui/widgets.h"

namespace ProtonEditor::Layers
{

EditorView::EditorView() : Layer("Editor View")
{
}

void EditorView::onAttach()
{
}

void EditorView::onImGuiRender()
{
    ProtonEngine::Ui::Widgets::Text("No project loaded");
}

void EditorView::onUpdate(float timeStep)
{
}

} // namespace ProtonEditor::Layers
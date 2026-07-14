/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "editor_view.h"

#include "protonengine/ui/widgets.h"

namespace ProtonEditor::Layers
{

EditorView::EditorView(const ProtonEngine::Renderer::Renderer & renderer)
    : Layer("Editor View")
    , m_renderer(renderer)
{
}
void EditorView::onAttach()
{
}

void EditorView::onImGuiRender()
{
    const auto size = ProtonEngine::Ui::Widgets::getWindowSize();
    ProtonEngine::Ui::Widgets::Image(m_renderer.getFrameBufferTexture(), size);
}

void EditorView::onUpdate(float timeStep)
{
}

} // namespace ProtonEditor::Layers
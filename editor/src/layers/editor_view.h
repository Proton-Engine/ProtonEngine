/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/renderer.h"
#include "protonengine/ui/ilayer.h"

namespace ProtonEditor::Layers
{

class EditorView : public ProtonEngine::Ui::Layer
{
public:
    explicit EditorView(const ProtonEngine::Renderer::Renderer & renderer);
    void onAttach() override;
    void onImGuiRender() override;
    void onUpdate(float timeStep) override;

private:
    const ProtonEngine::Renderer::Renderer & m_renderer;
};


} // namespace ProtonEditor::Layers

// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/ui/layer.h"

namespace ProtonEditor::Layers
{

class SceneHierarchyLayer : public ProtonEngine::Ui::Layer
{
public:
    SceneHierarchyLayer();

    void onAttach() override;
    void onImGuiRender() override;
    void onUpdate(float timeStep) override;
};


} // namespace ProtonEditor::Layers
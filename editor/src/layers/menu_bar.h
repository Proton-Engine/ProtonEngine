/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/ui/ilayer.h"

namespace ProtonEditor::Layers
{

class MenuBar : public ProtonEngine::Ui::Layer
{
public:
    MenuBar();
    void onAttach() override;
    void onImGuiRender() override;
    void onUpdate(float timeStep) override;

    [[nodiscard]] auto wantsWindow() const noexcept -> bool override { return false; }
};

} // namespace ProtonEditor::Layers
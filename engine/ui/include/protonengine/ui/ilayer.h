/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/ui/export.h"

namespace ProtonEngine::Ui
{

class PROTONENGINE_UI_EXPORT Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;
    Layer(Layer &) = delete;
    Layer(Layer &&) = default;
    Layer & operator=(Layer &) = delete;
    Layer & operator=(Layer &&) = default;

    virtual void onAttach() = 0;
    virtual void onImGuiRender() = 0;
    virtual void onUpdate(float timeStep) = 0;
};

} // namespace ProtonEngine::Ui
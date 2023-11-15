/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/proton_interface.h"

namespace ProtonEngine::UserInterface
{

class PROTON_API Layer
{
public:
    Layer() = default;
    virtual ~Layer() = default;
    Layer(Layer&) = delete;
    Layer(Layer&&) = default;
    Layer & operator=(Layer&) = delete;
    Layer & operator=(Layer&&) = default;

    virtual void onAttach() = 0;
    virtual void onImGuiRender() = 0;
    virtual void onUpdate(float timeStep) = 0;

    void begin();
    void end();
};

} // namespace ProtonEngine::UserInterface
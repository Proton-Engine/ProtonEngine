/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "layer.h"
#include "protonengine/proton_interface.h"

#include <chrono>

namespace ProtonEngine::UserInterface
{

class PROTON_API DebugLayer final : public Layer
{
public:
    void onAttach() override;
    void onImGuiRender() override;
    void onUpdate(float timeStep) override;

private:
    int m_totalFrames;
    int m_fps;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_nextTimePoint;
};

} // namespace ProtonEngine::UserInterface
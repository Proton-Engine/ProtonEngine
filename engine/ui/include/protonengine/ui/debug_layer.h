/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "ilayer.h"
#include "protonengine/ui/export.h"

#include <chrono>

namespace ProtonEngine::Ui
{

class PROTONENGINE_UI_EXPORT DebugLayer final : public Layer
{
public:
    void onAttach() override;
    void onImGuiRender() override;
    void onUpdate(float timeStep) override;

private:
    int m_totalFrames;
    int m_fps;
    std::chrono::microseconds m_frametime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_nextTimePoint;
};

} // namespace ProtonEngine::Ui
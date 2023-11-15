/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#include "..\include\protonengine\user_interface\debug_layer.h"

#include "imgui.h"

namespace ProtonEngine::UserInterface
{

void DebugLayer::onAttach()
{
    m_lastTimePoint = std::chrono::high_resolution_clock::now();
    m_nextTimePoint = m_lastTimePoint + std::chrono::seconds(1);
}

void DebugLayer::onImGuiRender()
{
    ImGui::Begin("Renderer debug");
    ImGui::Columns(2);

    ImGui::Text("Fps");
    ImGui::NextColumn();
    ImGui::Text("%i", m_fps);
    ImGui::NextColumn();

    ImGui::Text("Meshes");
    ImGui::NextColumn();
    ImGui::Text("n/a");
    ImGui::NextColumn();

    ImGui::Text("Draw calls");
    ImGui::NextColumn();
    ImGui::Text("n/a");
    ImGui::NextColumn();

    ImGui::End();
}

void DebugLayer::onUpdate(float timeStep)
{
    using namespace std::chrono;

    m_totalFrames++;

    const auto currentTime = high_resolution_clock::now();
    if (currentTime > m_nextTimePoint)
    {
        const auto sampleDuration = duration_cast<milliseconds>(currentTime - m_lastTimePoint);
        m_lastTimePoint = currentTime;
        m_nextTimePoint = currentTime + seconds(1);

        m_fps = static_cast<int>(static_cast<double>(m_totalFrames) / (sampleDuration.count() / 1'000.));
        m_totalFrames = 0;
    }
}

} // namespace ProtonEngine::UserInterface
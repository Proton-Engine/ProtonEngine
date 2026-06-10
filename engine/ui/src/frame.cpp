/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/ui/frame.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace ProtonEngine::Ui
{

void Frame::addLayer(std::unique_ptr<Layer> layer)
{
    layer->onAttach();
    m_layers.push_back(std::move(layer));
}

void Frame::onUpdate(float timeStep)
{
    for (const auto & layer : m_layers)
    {
        layer->onUpdate(timeStep);
    }
}

void Frame::render() const
{
    beginFrame();
    for (const auto & layer : m_layers)
    {
        if (layer->wantsWindow())
        {
            ImGui::Begin(layer->layerName().c_str());
        }
        layer->onImGuiRender();
        if (layer->wantsWindow())
        {
            ImGui::End();
        }
    }
    endFrame();
}

void Frame::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport();
}

void Frame::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace ProtonEngine::Ui
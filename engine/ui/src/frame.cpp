// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#include "protonengine/ui/frame.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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
        layer->onImGuiRender();
    }
    endFrame();
}

void Frame::beginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Frame::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
}
} // namespace ProtonEngine::Ui
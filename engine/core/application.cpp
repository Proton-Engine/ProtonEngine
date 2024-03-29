/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"

#include "protonengine/renderer/renderer.h"

#include "protonengine/components/camera.h"
#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"

#include "..\include\protonengine\user_interface\debug_layer.h"
#include "components/native_script.h"
#include "delta_time.h"
#include "fmt/core.h"
#include "input.h"
#include "protonengine/core/logger.h"
#include "window.h"

namespace ProtonEngine::Core
{

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
    // TODO: Do any engine initialization (like renderers here)
    PROTON_LOG_DEBUG("Initializing Proton Engine systems");
    m_window = std::make_unique<Window>(1280, 720, "Test title");
    Input::connectToEventBus();

    PROTON_LOG_INFO("Initializing user application");
    initialize();

    while (m_window->update())
    {
        DeltaTime::update();
        Renderer::update();

        const auto deltaTimeSeconds = static_cast<float>(DeltaTime::getDeltaTimeMicroSeconds().count()) / 1'000'000.0f;

        auto & registry = m_scene.getEntityRegistry();

        registry.view<Components::NativeScript>().each([&](Components::NativeScript & component) {
            component.onUpdate(deltaTimeSeconds);
        });

        registry.view<Components::Transform, Components::Camera>().each(Renderer::setCamera);
        registry.view<Components::Transform, Components::MeshRenderer>().each(Renderer::renderRenderableComponent);

        for (const auto & layer : m_layers)
        {
            layer->onUpdate(deltaTimeSeconds);
        }

        for (const auto & layer : m_layers)
        {
            layer->begin();
            layer->onImGuiRender();
            layer->end();
        }
    }
}

auto Application::getScene() noexcept -> Scene &
{
    return m_scene;
}

void Application::addLayer(std::unique_ptr<UserInterface::Layer> layer)
{
    layer->onAttach();
    m_layers.emplace_back(std::move(layer));
}

} // namespace ProtonEngine::Core
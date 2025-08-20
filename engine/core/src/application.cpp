/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"

#include "protonengine/core/components/camera_component.h"
#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/native_script.h"
#include "protonengine/core/components/transform_component.h"

#include "delta_time.h"
#include "protonengine/common/logger.h"
#include "protonengine/core/input.h"
#include "protonengine/renderer/irenderer.h"
#include "protonengine/ui/debug_layer.h"
#include "window.h"

namespace ProtonEngine::Core
{

Application::Application() = default;
Application::~Application() = default;

void Application::run()
{
    PROTON_LOG_DEBUG("Initializing Proton Engine systems");
    auto & renderer = Renderer::initializeRenderer(Renderer::RendererBackend::OPENGL);
    m_window = std::make_unique<Window>(1280, 720, "Test title", renderer);
    Input::connectToEventBus();

    PROTON_LOG_INFO("Initializing user application");
    initialize();

    while (m_window->update())
    {
        DeltaTime::update();
        renderer.update();

        const auto deltaTimeSeconds = static_cast<float>(DeltaTime::getDeltaTimeMicroSeconds().count()) / 1'000'000.0f;

        auto & registry = m_scene.getEntityRegistry();

        registry.view<Components::ScriptComponent>().each([&](Components::ScriptComponent & component) {
            component.nativeScript->onUpdate(deltaTimeSeconds);
        });

        registry.view<Components::TransformComponent, Components::CameraComponent>().each([&renderer](auto & transform, auto & camera) { renderer.setCamera(transform.transform, camera.camera); });
        registry.view<Components::TransformComponent, Components::MeshRenderer>().each([&renderer](auto & transform, auto & meshRenderer) {
            renderer.addToRenderQueue(transform.transform, meshRenderer.mesh, meshRenderer.texture, meshRenderer.material);
        });
        renderer.renderAllInQueue();

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

void Application::addLayer(std::unique_ptr<Ui::Layer> layer)
{
    layer->onAttach();
    m_layers.emplace_back(std::move(layer));
}

} // namespace ProtonEngine::Core
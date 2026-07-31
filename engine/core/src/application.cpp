/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"

#include "protonengine/core/components/camera_component.h"
#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/native_script.h"
#include "protonengine/core/components/transform_component.h"

#include "delta_time.h"
#include "protonengine/common/logger.h"
#include "protonengine/core/components/light_component.h"
#include "protonengine/core/input.h"
#include "protonengine/renderer/irender_backend.h"
#include "protonengine/renderer/renderer.h"
#include "protonengine/ui/debug_layer.h"
#include "window.h"

namespace ProtonEngine::Core
{

Application::Application() = default;
Application::~Application() = default;

void Application::run()
{
    PROTON_LOG_DEBUG("Initializing Proton Engine systems");
    m_renderer = std::make_unique<Renderer::Renderer>(Renderer::Renderer::RendererBackend::OPENGL);
    m_window = std::make_unique<Window>(1280, 720, "Test title", *m_renderer);
    Input::connectToEventBus();

    PROTON_LOG_INFO("Initializing user application");
    initialize();

    while (m_window->update())
    {
        DeltaTime::update();

        const auto deltaTimeSeconds = static_cast<float>(DeltaTime::getDeltaTimeMicroSeconds().count()) / 1'000'000.0f;

        auto & registry = m_scene.getEntityRegistry();

        registry.view<Components::ScriptComponent>().each([&](Components::ScriptComponent & component) {
            component.nativeScript->onUpdate(deltaTimeSeconds);
        });

        registry.view<Components::TransformComponent, Components::CameraComponent>().each([&](auto & transform, auto & camera) { m_renderer->addCamera(transform.transform, camera.camera); });
        registry.view<Components::TransformComponent, Components::MeshRenderer>().each([&](auto & transform, auto & meshRenderer) {
            m_renderer->addToRenderQueue(transform.transform, meshRenderer.mesh, meshRenderer.material);
        });
        registry.view<Components::TransformComponent, Components::LightComponent>().each([&](auto & transform, auto & light) {
            m_renderer->addLight(transform.transform, light.light);
        });
        m_renderer->renderAllInQueue();

        m_uiFrame.onUpdate(deltaTimeSeconds);
        m_uiFrame.render();
    }
}

auto Application::getScene() noexcept -> Scene &
{
    return m_scene;
}

auto Application::renderer() noexcept -> Renderer::Renderer &
{
    assert(m_renderer);
    return *m_renderer;
}

void Application::setVSync(bool enabled) noexcept
{
    assert(m_window);
    m_window->setVSync(enabled);
}

void Application::addLayer(std::unique_ptr<Ui::Layer> layer)
{
    m_uiFrame.addLayer(std::move(layer));
}

} // namespace ProtonEngine::Core
/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"

#include "protonengine/renderer/renderer.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"
#include "protonengine/components/camera.h"

#include "window.h"
#include "delta_time.h"
#include "components/native_script.h"

#include "glad/glad.h"

namespace ProtonEngine::Core
{

ProtonEngine::Core::Application::Application() :
    m_window(std::make_unique<Window>(1280, 720, "Test title"))
{
}

Application::~Application()
{
}

auto Application::getScene() noexcept -> Scene &
{
    return m_scene;
}

void Application::run()
{
    while(m_window->update())
    {
        DeltaTime::update();

        const auto deltaTimeSeconds = static_cast<float>(DeltaTime::getDeltaTimeMicroSeconds().count()) / 1'000'000.0f ;

        auto & registry = m_scene.getEntityRegistry();

        registry.view<Components::NativeScript>().each([&](Components::NativeScript & component) {
            component.onUpdate(deltaTimeSeconds);
        });

        registry.view<Components::Transform, Components::Camera>().each(Renderer::setCamera);
        registry.view<Components::Transform, Components::MeshRenderer>().each(Renderer::renderRenderableComponent);
    }
}

} // namespace ProtonEngine::Core
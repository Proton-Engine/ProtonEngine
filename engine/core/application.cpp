/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"
#include "protonengine/core/entity.h"

#include "protonengine/renderer/renderer.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"
#include "protonengine/components/camera.h"
#include "protonengine/components/proton_script.h"

#include "window.h"
#include "delta_time.h"
#include "input.h"
#include "components/native_script.h"

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

        const auto deltaTimeSeconds = static_cast<double>(DeltaTime::getDeltaTimeMicroSeconds().count()) / 1'000'000.0 ;

        auto & registry = m_scene.getEntityRegistry();

        registry.view<Components::NativeScript>().each([&](Components::NativeScript & component) { component.onUpdate(deltaTimeSeconds); });

        registry.view<Components::Transform, Components::Camera>().each(Renderer::setCamera);
        registry.view<Components::Transform, Components::MeshRenderer>().each(Renderer::renderRenderableComponent);
    }
}

} // namespace ProtonEngine::Core
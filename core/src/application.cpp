/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"
#include "protonengine/core/entity.h"

#include "protonengine/renderer/renderer.h"

#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/transform.h"
#include "window.h"

namespace ProtonEngine::Core
{

ProtonEngine::Core::Application::Application() :
    m_window(std::make_unique<Window>(1280, 720, "Test title"))
{
}

Application::~Application()
{
}

void Application::update()
{
    m_window->update();

    auto & registry = m_scene.getEntityRegistry();

    registry.view<Components::Transform, Components::MeshRenderer>().each(Renderer::renderRenderableComponent);
}

auto Application::getScene() noexcept -> Scene &
{
    return m_scene;
}

} // namespace ProtonEngine::Core
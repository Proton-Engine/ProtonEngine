/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"
#include "protonengine/core/cube.h"
#include "protonengine/core/triangle.h"

#include "protonengine/renderer/renderer.h"
#include "protonengine/core/entity.h"

#include <entt/entt.hpp>

namespace ProtonEngine::Core {

ProtonEngine::Core::Application::Application() :
    m_window(1280, 720, "Test title")
{
}

Application::~Application()
{
}

auto Application::getWindow() const noexcept -> const Window &
{
    return m_window;
}

void Application::update()
{
    m_window.update();

//    static Cube cube;
//    static Triangle triangle;

    auto & registry = m_scene.getEntityRegistry();

    registry.view<TransformComponent, RenderableComponent>().each(Renderer::renderRenderableComponent);
}

auto Application::getScene() noexcept -> Scene &
{
    return m_scene;
}

} // namespace ProtonEngine::Core
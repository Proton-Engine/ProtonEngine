/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"
#include "protonengine/core/cube.h"
#include "protonengine/core/triangle.h"

#include "protonengine/renderer/renderer.h"

namespace ProtonEngine::Core {

ProtonEngine::Core::Application::Application() :
    m_window(1280, 720, "Test title")
{
}

Application::~Application()
{
}

const Window & Application::getWindow()
{
    return m_window;
}

void Application::update()
{
    m_window.update();

    static Cube cube;
    static Triangle triangle;

    Renderer::renderFrame(cube, triangle);
}

} // namespace ProtonEngine::Core
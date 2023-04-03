/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"
#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/mesh.h"

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

    static const std::vector<float> g_vertex_buffer_data = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    static ProtonEngine::Renderer::Mesh mesh(g_vertex_buffer_data);

    Renderer::renderFrame(mesh);
}

} // namespace ProtonEngine::Core
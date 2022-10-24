/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/application.h"

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
}

} // namespace ProtonEngine::Core
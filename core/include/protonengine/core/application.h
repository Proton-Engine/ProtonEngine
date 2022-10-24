/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "window.h"

namespace ProtonEngine::Core
{

class Application
{
public:
    Application();
    virtual ~Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;

    virtual void initialize() = 0;

    const Window & getWindow();

private:
    Window m_window;
};

} // namespace ProtonEngine
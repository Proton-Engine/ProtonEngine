/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "window.h"
#include "scene.h"

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

    void update();

    [[nodiscard]] auto getWindow() const noexcept -> const Window &;
    [[nodiscard]] auto getScene() noexcept -> Scene &;

private:
    Window m_window;
    Scene m_scene;
};

} // namespace ProtonEngine
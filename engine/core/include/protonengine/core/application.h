/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "scene.h"

#include <memory>

namespace ProtonEngine::Core
{

class Window;

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

    [[nodiscard]] auto getScene() noexcept -> Scene &;

private:
    std::unique_ptr<Window> m_window;
    Scene m_scene;
};

} // namespace ProtonEngine
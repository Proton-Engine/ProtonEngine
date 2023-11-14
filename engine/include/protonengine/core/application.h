/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/scene.h"
#include "protonengine/proton_interface.h"

#include <memory>

namespace ProtonEngine::Core
{

class Window;

class PROTON_API Application
{
public:
    Application();
    virtual ~Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;

    virtual void initialize() = 0;

    void run();

    [[nodiscard]] auto getScene() noexcept -> Scene &;

private:
    std::unique_ptr<Window> m_window;
    Scene m_scene;
};

} // namespace ProtonEngine
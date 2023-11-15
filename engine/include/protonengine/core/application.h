/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/scene.h"
#include "protonengine/proton_interface.h"
#include "protonengine/user_interface/layer.h"

#include <memory>
#include <vector>

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

protected:
    void addLayer(std::unique_ptr<UserInterface::Layer> layer);

private:
    std::unique_ptr<Window> m_window;
    std::vector<std::unique_ptr<UserInterface::Layer>> m_layers;
    Scene m_scene;
};

} // namespace ProtonEngine
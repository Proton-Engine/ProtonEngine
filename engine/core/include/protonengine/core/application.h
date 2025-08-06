/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"
#include "protonengine/core/scene.h"
#include "protonengine/ui/layer.h"

#include <memory>
#include <vector>

namespace ProtonEngine::Core
{

class Window;

class PROTONENGINE_CORE_EXPORT Application
{
public:
    Application();
    virtual ~Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application & operator=(const Application &) = delete;
    Application & operator=(Application &&) = delete;

    void run();

    [[nodiscard]] auto getScene() noexcept -> Scene &;

protected:
    virtual void initialize() = 0;
    void addLayer(std::unique_ptr<UserInterface::Layer> layer);

private:
    std::unique_ptr<Window> m_window;
    std::vector<std::unique_ptr<UserInterface::Layer>> m_layers;
    Scene m_scene;
};

} // namespace ProtonEngine::Core
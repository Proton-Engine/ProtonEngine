/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/export.h"
#include "protonengine/core/scene.h"
#include "protonengine/renderer/renderer.h"
#include "protonengine/ui/frame.h"
#include "protonengine/ui/ilayer.h"

#include <memory>
#include <vector>

namespace ProtonEngine::Core
{

class Window;

class PROTONENGINE_EXPORT Application
{
public:
    Application();
    virtual ~Application();
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application & operator=(const Application &) = delete;
    Application & operator=(Application &&) = delete;

    void run();
    void setVSync(bool enabled) noexcept;

    [[nodiscard]] auto getScene() noexcept -> Scene &;
    [[nodiscard]] auto renderer() noexcept -> Renderer::Renderer &;

protected:
    virtual void initialize() = 0;
    void addLayer(std::unique_ptr<Ui::Layer> layer);

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer::Renderer> m_renderer;

    Ui::Frame m_uiFrame;
    Scene m_scene;
};

} // namespace ProtonEngine::Core
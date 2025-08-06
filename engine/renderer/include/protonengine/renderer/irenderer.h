/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"

#include "protonengine/components/camera.h"
#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void * (*)(const char * name);

class PROTONENGINE_RENDERER_EXPORT IRenderer
{
public:
    virtual ~IRenderer() = default;
    IRenderer(IRenderer &) = delete;
    IRenderer(IRenderer &&) = delete;
    IRenderer & operator=(IRenderer &) = delete;
    IRenderer & operator=(IRenderer &&) = delete;

    virtual void setWindowContext(ContextLoadFunction func) = 0;

    virtual void addToRenderQueue(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer) = 0;
    virtual void renderAllInQueue() = 0;
    virtual void setCamera(const Components::Transform & transform, const Components::Camera & camera) = 0;
    virtual void update() = 0;

protected:
    IRenderer() = default;
};

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/proton_interface.h"

#include "protonengine/components/camera.h"
#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

class PROTON_API IRenderer
{
public:
    virtual ~IRenderer() = default;
    IRenderer(IRenderer &) = delete;
    IRenderer(IRenderer &&) = delete;
    IRenderer& operator=(IRenderer&) = delete;
    IRenderer& operator=(IRenderer&&) = delete;

    virtual void setWindowContext(ContextLoadFunction func) = 0;

    virtual void addToRenderQueue(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer) = 0;
    virtual void renderAllInQueue() = 0;
    virtual void setCamera(const Components::Transform & transform, const Components::Camera & camera) = 0;
    virtual void update() = 0;
protected:
    IRenderer() = default;
};

}
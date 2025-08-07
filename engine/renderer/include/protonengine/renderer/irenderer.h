/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/camera.h"
#include "protonengine/renderer/export.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"
#include "protonengine/renderer/transform.h"

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

    virtual void addToRenderQueue(const Transform & transform, const Mesh & mesh, const Texture & texture) = 0;
    virtual void renderAllInQueue() = 0;
    virtual void setCamera(const Transform & transform, const Camera & camera) = 0;
    virtual void update() = 0;

protected:
    IRenderer() = default;
};

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/camera.h"
#include "protonengine/renderer/transform.h"

namespace ProtonEngine::Renderer
{

// TODO: Don't have these as pointers
struct RenderableCamera
{
    const Transform * transform;
    const Camera * camera;
};

} // namespace ProtonEngine::Renderer
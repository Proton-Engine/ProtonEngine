/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/material.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/transform.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Transform & transform;
    const Mesh & mesh;
    const Material & material;
};

} // namespace ProtonEngine::Renderer
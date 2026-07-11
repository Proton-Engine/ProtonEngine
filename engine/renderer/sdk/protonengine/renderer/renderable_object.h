/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "material.h"
#include "mesh.h"
#include "transform.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Transform & transform;
    const Mesh & mesh;
    const Material & material;
};

} // namespace ProtonEngine::Renderer
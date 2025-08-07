/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"
#include "protonengine/renderer/transform.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Transform & transform;
    const Mesh & mesh;
    const Texture & texture;
};

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/components/transform.h"
#include "protonengine/components/mesh_renderer.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Components::Transform & transform;
    const Components::MeshRenderer & meshRenderer;
};

} // namespace ProtonEngine::Renderer
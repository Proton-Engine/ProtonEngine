/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/core/components/transform.h"
#include "protonengine/core/components/mesh_renderer.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Core::Components::Transform & transform;
    const Core::Components::MeshRenderer & meshRenderer;
};

} // namespace ProtonEngine::Renderer
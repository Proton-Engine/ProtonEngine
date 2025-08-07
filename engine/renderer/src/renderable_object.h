/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/transform_component.h"

namespace ProtonEngine::Renderer
{

struct RenderableObject
{
    const Transform & transform;
    const Core::Components::MeshRenderer & meshRenderer;
};

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/components/export.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"


namespace ProtonEngine::Components
{

struct PROTONENGINE_COMPONENTS_EXPORT MeshRenderer
{
    Renderer::Mesh & mesh;
    Renderer::Texture & texture;
};

} // namespace ProtonEngine::Components
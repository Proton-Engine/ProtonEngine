/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"


namespace ProtonEngine::Core::Components
{

struct PROTONENGINE_CORE_EXPORT MeshRenderer
{
    Renderer::Mesh & mesh;
    Renderer::Texture & texture;

    MeshRenderer(Renderer::Mesh & mesh, Renderer::Texture & texture) :
        mesh(mesh),
        texture(texture) {}
};

} // namespace ProtonEngine::Core::Components
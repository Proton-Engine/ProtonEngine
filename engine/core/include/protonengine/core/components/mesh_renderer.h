/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/material.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"


namespace ProtonEngine::Core::Components
{

struct MeshRenderer
{
    Renderer::Mesh & mesh;
    Renderer::Material & material;

    MeshRenderer(Renderer::Mesh & mesh, Renderer::Material & material) :
        mesh(mesh),
        material(material)
    {
    }
};

} // namespace ProtonEngine::Core::Components
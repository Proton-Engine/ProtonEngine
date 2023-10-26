/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"

#include <optional>

namespace ProtonEngine::Core::Components
{

struct MeshRenderer
{
    Renderer::Mesh & mesh;
    Renderer::Texture & texture;
};

} // namespace ProtonEngine::Core
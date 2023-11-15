/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"
#include "protonengine/proton_interface.h"

#include <optional>

namespace ProtonEngine::Components
{

struct PROTON_API MeshRenderer
{
    Renderer::Mesh & mesh;
    Renderer::Texture & texture;
};

} // namespace ProtonEngine::Components
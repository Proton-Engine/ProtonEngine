/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"

#include <string>
#include <memory>

namespace ProtonEngine::Core
{

struct TagComponent
{
    std::string tag;
};

struct RenderableComponent
{
    Renderer::Mesh & mesh;
};

} // namespace ProtonEngine::Core
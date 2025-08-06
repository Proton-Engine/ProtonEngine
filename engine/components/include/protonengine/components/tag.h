/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/components/export.h"
#include "protonengine/renderer/mesh.h"

#include <glm/vec3.hpp>

#include <memory>
#include <string>

namespace ProtonEngine::Components
{

struct PROTONENGINE_COMPONENTS_EXPORT Tag
{
    std::string tag;
};

} // namespace ProtonEngine::Components
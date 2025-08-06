/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"
#include "protonengine/renderer/mesh.h"

#include <glm/vec3.hpp>

#include <memory>
#include <string>

namespace ProtonEngine::Core::Components
{

struct PROTONENGINE_CORE_EXPORT Tag
{
    std::string tag;
};

} // namespace ProtonEngine::Core::Components
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Core::Components
{

struct PROTONENGINE_CORE_EXPORT Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) :
        position(position),
        rotation(rotation),
        scale(scale) {}

    Transform() = default;
};

} // namespace ProtonEngine::Core::Components
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/components/export.h"

#include <glm/vec3.hpp>

#include <memory>
#include <string>

namespace ProtonEngine::Components
{

struct PROTONENGINE_COMPONENTS_EXPORT Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

} // namespace ProtonEngine::Components
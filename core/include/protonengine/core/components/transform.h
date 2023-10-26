/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"

#include <glm/vec3.hpp>

#include <string>
#include <memory>

namespace ProtonEngine::Core::Components
{

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

} // namespace ProtonEngine::Core
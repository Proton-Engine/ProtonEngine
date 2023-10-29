/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <glm/vec3.hpp>

#include <string>
#include <memory>

namespace ProtonEngine::Components
{

struct PROTON_API Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

} // namespace ProtonEngine::Components
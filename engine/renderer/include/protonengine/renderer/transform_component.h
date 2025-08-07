/*
 * Copyright © 2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once
#include "glm/vec3.hpp"

namespace ProtonEngine::Renderer
{

struct Transform
{
    Transform() = default;

    Transform(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) :
         position(position),
         rotation(rotation),
         scale(scale) {}

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

} // namespace ProtonEngine::Renderer

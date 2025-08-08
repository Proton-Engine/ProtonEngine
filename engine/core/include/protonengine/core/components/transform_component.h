/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/transform.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Core::Components
{

struct TransformComponent
{
    TransformComponent() :
        TransformComponent(glm::vec3(0), glm::vec3(0), glm::vec3(1))
    {
    }

    TransformComponent(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) :
        transform(position, rotation, scale)
    {
    }

    Renderer::Transform transform;
    // TODO: Add a way to reference the RendererTransform fields
    // glm::vec3 & position;
    // glm::vec3 & rotation;
    // glm::vec3 & scale;
};

} // namespace ProtonEngine::Core::Components
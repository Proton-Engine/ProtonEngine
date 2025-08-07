/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/transform_component.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Core::Components
{

struct TransformComponent
{
    TransformComponent() = default;

    TransformComponent(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) :
        transform(position, rotation, scale)
    {
    }

    Renderer::Transform transform;
};

} // namespace ProtonEngine::Core::Components
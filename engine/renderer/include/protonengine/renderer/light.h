/*
* Copyright © 2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <glm/vec3.hpp>

namespace ProtonEngine::Renderer
{

enum class LightType
{
    DIRECTIONAL,
    POINT,
    // SPOTLIGHT
};

struct Light
{
    LightType type;
    glm::vec3 color;
    float intensity;
};

} // namespace ProtonEngine::Core::Components
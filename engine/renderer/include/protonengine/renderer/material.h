// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "glm/vec3.hpp"

namespace ProtonEngine::Renderer
{

struct Material
{
    glm::vec3 ambientColor = glm::vec3(1.0f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(1.0f);
    float shininess = 32.0f;
};

} // namespace ProtonEngine::Renderer

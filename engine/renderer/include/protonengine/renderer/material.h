// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/texture.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Renderer
{

[[nodiscard]] PROTONENGINE_RENDERER_EXPORT auto getDefaultTexture() -> Texture &;

struct Material
{
    glm::vec3 baseColor = glm::vec3(1.0f);
    // TODO: Remove dependency to the irenderer.h from this file
    Texture & baseTexture = getDefaultTexture();
    glm::vec3 specularColor = glm::vec3(0.5f);
    Texture & specularMap = getDefaultTexture();
    float shininess = 32.0f;
};

} // namespace ProtonEngine::Renderer

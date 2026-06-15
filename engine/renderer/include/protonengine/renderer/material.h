// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "itexture.h"

#include "protonengine/renderer/export.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Renderer
{

// TODO: Why is this here?
[[nodiscard]] PROTONENGINE_RENDERER_EXPORT auto getDefaultTexture() -> ITexture &;

struct Material
{
    glm::vec3 baseColor = glm::vec3(1.0f);
    // TODO: Remove dependency to the irenderer.h from this file
    ITexture & baseTexture = getDefaultTexture();
    glm::vec3 specularColor = glm::vec3(0.5f);
    ITexture & specularMap = getDefaultTexture();
    float shininess = 32.0f;
};

} // namespace ProtonEngine::Renderer

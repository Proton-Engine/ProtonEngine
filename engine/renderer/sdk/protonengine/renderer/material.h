/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/itexture.h"

#include <glm/vec3.hpp>

namespace ProtonEngine::Renderer
{

struct Material
{
    Material(glm::vec3 baseColor, ITexture & baseTexture, glm::vec3 specularColor, ITexture & specularMap, float shininess)
        : baseColor(baseColor)
        , baseTexture(baseTexture)
        , specularColor(specularColor)
        , specularMap(specularMap)
        , shininess(shininess)
    {
    }
    
    glm::vec3 baseColor;
    ITexture & baseTexture;
    glm::vec3 specularColor;
    ITexture & specularMap;
    float shininess;
};

} // namespace ProtonEngine::Renderer

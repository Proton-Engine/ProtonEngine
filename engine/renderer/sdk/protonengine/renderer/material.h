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
    Material(glm::vec3 baseColor,
             ITexture & baseTexture,
             glm::vec3 specularColor,
             ITexture & specularMap,
             float shininess,
             float ambientIntensity = 0.1f)
        : baseColor(baseColor)
        , baseTexture(baseTexture)
        , specularColor(specularColor)
        , specularMap(specularMap)
        , shininess(shininess)
        , ambientIntensity(ambientIntensity)
    {
    }
    
    glm::vec3 baseColor;
    ITexture & baseTexture;
    glm::vec3 specularColor;
    ITexture & specularMap;
    float shininess;
    float ambientIntensity;
};

} // namespace ProtonEngine::Renderer

/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/material.h"

namespace ProtonEngine::Renderer
{

Material::Material(glm::vec3 baseColor, ITexture & baseTexture, glm::vec3 specularColor, ITexture & specularMap, float shininess) : baseColor(baseColor), baseTexture(baseTexture), specularColor(specularColor), specularMap(specularMap), shininess(shininess)
{
}

} // namespace ProtonEngine::Renderer
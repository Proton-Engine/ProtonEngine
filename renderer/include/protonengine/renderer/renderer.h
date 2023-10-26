/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "mesh.h"
#include "texture.h"

#include "protonengine/core/assets/image.h"
#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/transform.h"

#include <string_view>

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

void setWindowContext(ContextLoadFunction func);
void renderRenderableComponent(const Core::Components::Transform & transform, const Core::Components::MeshRenderer & meshRenderer);

Texture createTextureFromImage(const Core::Assets::Image & image);

} // namespace ProtonEngine::Renderer
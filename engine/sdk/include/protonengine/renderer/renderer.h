/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "mesh.h"
#include "texture.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"
#include "protonengine/components/camera.h"

#include "protonengine/assets/image.h"

#include <string_view>

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

void setWindowContext(ContextLoadFunction func);
void setCamera(const Components::Transform & transform, const Components::Camera & camera);
void renderRenderableComponent(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer);

Texture createTextureFromImage(const Assets::Image & image);

} // namespace ProtonEngine::Renderer
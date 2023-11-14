/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/texture.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/transform.h"
#include "protonengine/components/camera.h"

#include "protonengine/assets/image.h"

#include <string_view>

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

PROTON_API void setWindowContext(ContextLoadFunction func);
PROTON_API void setCamera(const Components::Transform & transform, const Components::Camera & camera);
PROTON_API void renderRenderableComponent(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer);

[[nodiscard]] PROTON_API Texture createTextureFromImage(const Assets::Image & image);

} // namespace ProtonEngine::Renderer
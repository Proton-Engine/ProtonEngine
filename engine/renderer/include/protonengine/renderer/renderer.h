/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"

#include "protonengine/assets/image.h"
#include "protonengine/renderer/irenderer.h"
#include "protonengine/renderer/texture.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void * (*)(const char * name);

enum class RendererBackend
{
    OPENGL
};

[[nodiscard]] PROTONENGINE_COMPONENTS_EXPORT auto initializeRenderer(RendererBackend rendererBackend) -> IRenderer &;
[[nodiscard]] PROTONENGINE_RENDERER_EXPORT Texture createTextureFromImage(const Assets::Image & image);

} // namespace ProtonEngine::Renderer
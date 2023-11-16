/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include "protonengine/renderer/texture.h"

#include "protonengine/assets/image.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

[[nodiscard]] PROTON_API Texture createTextureFromImage(const Assets::Image & image);

} // namespace ProtonEngine::Renderer
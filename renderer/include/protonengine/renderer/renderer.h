/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "mesh.h"
#include "protonengine/core/components.h"

#include <string_view>

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

void setWindowContext(ContextLoadFunction func);
void renderRenderableComponent(const Core::TransformComponent & transform, const Core::RenderableComponent & renderable);

uint32_t loadTexture(std::string_view path);

} // namespace ProtonEngine::Renderer
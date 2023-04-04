/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "mesh.h"

#include <string_view>

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void* (*)(const char *name);

void setWindowContext(ContextLoadFunction func);
void renderFrame(const Mesh & mesh, const Mesh & mesh2);

uint32_t loadTexture(std::string_view path);

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <concepts>

namespace ProtonEngine::Renderer
{

using ContextLoadFunctionReturn = void (*)();
using ContextLoadFunction = ContextLoadFunctionReturn (*)(const char *name);

void setWindowContext(ContextLoadFunction func);
void update();

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ishader.h"

#include <memory>

namespace ProtonEngine::Renderer
{

// TODO: Create an IPipeline struct that internally can manage the rendering pipeline
struct Pipeline
{
    std::unique_ptr<IShader> shader;
};

} // namespace ProtonEngine::Renderer

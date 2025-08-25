// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/light.h"
#include "protonengine/renderer/transform.h"

namespace ProtonEngine::Renderer
{

struct RenderableLight
{
    const Transform & transform;
    const Light & light;
};

} // namespace ProtonEngine::Renderer

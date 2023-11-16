/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/proton_interface.h"
#include "protonengine/renderer/irenderer.h"

namespace ProtonEngine::Renderer
{

enum class RendererBackend
{
    OPENGL
};

PROTON_API [[nodiscard]] auto initializeRenderer(RendererBackend rendererBackend) -> IRenderer&;

} // namespace ProtonEngine::Renderer
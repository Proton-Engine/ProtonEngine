/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/common/logger.h"

#include "protonengine/core/event_bus.h"

#include "opengl/opengl_renderer.h"

#include <stdexcept>

namespace ProtonEngine::Renderer
{

auto initializeRenderer(RendererBackend rendererBackend) -> IRenderer &
{
    if (rendererBackend != RendererBackend::OPENGL)
    {
        PROTON_LOG_ERROR("Renderer backend other than OpenGL are not supported");
        throw std::runtime_error("Renderer backend other than OpenGL are not supported");
    }

    static OpenGL::OpenGLRenderer renderer;
    return renderer;
}

Texture createTextureFromImage(const Assets::Image & image)
{
    return Texture(image);
}

} // namespace ProtonEngine::Renderer

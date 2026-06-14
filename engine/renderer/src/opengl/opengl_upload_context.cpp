/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_upload_context.h"

#include "opengl_buffer.h"

namespace ProtonEngine::Renderer::OpenGL
{

void OpenGLUploadContext::uploadBuffer(const IBuffer & destination, std::span<const std::byte> source, uint16_t offset)
{
    const auto openglBuffer = static_cast<const Buffer *>(&destination);
    openglBuffer->bind();
    openglBuffer->setData(source);
    openglBuffer->unbind();
}

} // namespace ProtonEngine::Renderer::OpenGL
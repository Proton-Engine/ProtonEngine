/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_upload_context.h"

#include "opengl_buffer.h"
#include "opengl_texture.h"

#include <glad/gl.h>


namespace ProtonEngine::Renderer::OpenGL
{

void OpenGLUploadContext::uploadBuffer(const IBuffer & destination, std::span<const std::byte> source, [[maybe_unused]] uint16_t offset)
{
    // TODO: Load into buffer with opengl here
    const auto & openglBuffer = static_cast<const Buffer &>(destination);
    openglBuffer.bind();
    openglBuffer.setData(source);
    openglBuffer.unbind();
}

void OpenGLUploadContext::uploadTexture(const ITexture & texture, const Assets::Image & image)
{
    const auto & openglTexture = static_cast<const OpenGLTexture &>(texture);
    const auto dataFormat = openglTexture.getDataFormat();
    const auto internalDataFormat = openglTexture.getInternalDataFormat();

    // TODO: We have to bind it here somehow, let's find a different way to do this
    openglTexture.bind(0);
    glTexImage2D(GL_TEXTURE_2D, 0, internalDataFormat, image.getWidth(), image.getHeight(),
                 0, dataFormat, GL_UNSIGNED_BYTE, image.getData());
    openglTexture.unbind(0);
}

} // namespace ProtonEngine::Renderer::OpenGL
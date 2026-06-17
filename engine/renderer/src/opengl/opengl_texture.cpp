// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "opengl_texture.h"

#include "protonengine/common/logger.h"

#include <glad/gl.h>

#include <cassert>
#include <format>

namespace ProtonEngine::Renderer::OpenGL
{

OpenGLTexture::OpenGLTexture(const TextureDescriptor & descriptor) : m_descriptor{descriptor}
{
    PROTON_LOG_DEBUG(std::format("Loading image {} into texture buffers", "__insert_image_name__"));

    switch (descriptor.format)
    {
    case TextureFormat::RGB8:
        m_internalDataFormat = GL_RGB8;
        m_dataFormat = GL_RGB;
        break;
    case TextureFormat::RGBA8:
        m_internalDataFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;
        break;
    }

    glGenTextures(1, &m_textureID);
}

OpenGLTexture::~OpenGLTexture()
{
    glDeleteTextures(1, &m_textureID);
}

auto OpenGLTexture::getDescriptor() const -> TextureDescriptor
{
    return m_descriptor;
}

void OpenGLTexture::bind(uint32_t slot) const noexcept
{
    assert(GL_TEXTURE0 + slot < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void OpenGLTexture::unbind(uint32_t slot) const noexcept
{
    assert(GL_TEXTURE0 + slot < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto OpenGLTexture::getDataFormat() const noexcept -> uint32_t
{
    return m_dataFormat;
}

auto OpenGLTexture::getInternalDataFormat() const noexcept -> uint32_t
{
    return m_internalDataFormat;
}

} // namespace ProtonEngine::Renderer::OpenGL

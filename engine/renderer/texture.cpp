/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/texture.h"

#include "glad/glad.h"
#include "fmt/core.h"

namespace ProtonEngine::Renderer
{

Texture::Texture(const Assets::Image & image)
{
    auto data = image.getData();
    GLenum internalFormat = 0;
    GLenum dataFormat = 0;

    if (image.getChannels() == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (image.getChannels() == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.getWidth(), image.getHeight(), 0, dataFormat, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activate() const
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::deactivate() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace ProtonEngine::Renderer
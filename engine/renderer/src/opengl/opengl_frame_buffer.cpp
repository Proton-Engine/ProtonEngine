/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_frame_buffer.h"

#include "opengl_renderer.h"
#include "opengl_texture.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irender_backend.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer::OpenGL
{

OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferDescriptor & descriptor, const OpenGLRenderer & renderBackend)
{
    glGenFramebuffers(1, &m_frameBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

    TextureDescriptor colorAttachmentDescriptor{
        descriptor.width,
        descriptor.height, TextureFormat::RGB8};

    m_colorTexture = renderBackend.createTexture(colorAttachmentDescriptor);
    const auto openglColorTexture = static_cast<OpenGLTexture *>(m_colorTexture.get());

    glBindTexture(GL_TEXTURE_2D, openglColorTexture->id());
    glTexImage2D(GL_TEXTURE_2D, 0, openglColorTexture->getInternalDataFormat(), descriptor.width, descriptor.height, 0, openglColorTexture->getDataFormat(), GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &m_renderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, openglColorTexture->id(), 0);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, descriptor.width, descriptor.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_frameBufferId);

    // TODO: Do we need to access this?
    // TextureDescriptor depthStencilAttachmentDescriptor{
    //     descriptor.width,
    //     descriptor.height, TextureFormat::DEPTH_STENCIL};
    //
    // m_depthStencilTexture = renderBackend.createTexture(depthStencilAttachmentDescriptor);
    // const auto openglDepthStencilTexture = static_cast<OpenGLTexture *>(m_depthStencilTexture.get());
    //
    // glBindTexture(GL_TEXTURE_2D, openglDepthStencilTexture->id());
    // glTexImage2D(GL_TEXTURE_2D, 0, openglDepthStencilTexture->getInternalDataFormat(), descriptor.width, descriptor.height, 0, openglDepthStencilTexture->getDataFormat(), GL_UNSIGNED_BYTE, nullptr);
    // glBindTexture(GL_TEXTURE_2D, 0);
    //
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, openglDepthStencilTexture->id(), 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        PROTON_LOG_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
    glDeleteFramebuffers(1, &m_frameBufferId);
}

auto OpenGLFrameBuffer::colorTexture() -> const ITexture &
{
    return *m_colorTexture;
}

auto OpenGLFrameBuffer::id() const -> uint32_t
{
    return m_frameBufferId;
}

} // namespace ProtonEngine::Renderer::OpenGL

/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_renderer.h"

#include "opengl_buffer.h"
#include "opengl_descriptor_set.h"
#include "opengl_frame_buffer.h"
#include "opengl_pipeline.h"
#include "opengl_sampler.h"
#include "opengl_shader.h"
#include "opengl_texture.h"

#include "protonengine/common/event_bus.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irender_backend.h"
#include "protonengine/renderer/ishader.h"

#include <glad/gl.h>

#include <format>
#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

void GLAPIENTRY
    MessageCallback(GLenum /*source*/,
                    GLenum type,
                    GLuint /*id*/,
                    GLenum severity,
                    GLsizei /*length*/,
                    const GLchar * message,
                    const void * /*userParam*/)
{
    if (type != GL_DEBUG_TYPE_ERROR)
    {
        PROTON_LOG_TRACE(std::format("GL CALLBACK: type = {:#x}, severity = {:#x}, message = {}", type, severity, message));
        return;
    }

    std::string messageType = (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "");
    PROTON_LOG_ERROR(std::format("GL CALLBACK: {} type = {:#x}, severity = {:#x}, message = {}", messageType, type, severity, message));
}

void OpenGLRenderer::setWindowContext(ContextLoadFunction func)
{
    const auto version = gladLoadGL(func);
    if (version == 0)
    {
        PROTON_LOG_ERROR("Failed to initialize OpenGL context");
        throw std::runtime_error("Failed to initialize OpenGL context");
    }

    // TODO: Move to an initialize for the renderer
#ifndef __APPLE__
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void OpenGLRenderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    glViewport(x, y, width, height);
}

auto OpenGLRenderer::createPipeline(PipelineDescriptor && descriptor) const -> std::unique_ptr<IPipeline>
{
    return std::make_unique<OpenGLPipeline>(std::move(descriptor));
}

auto OpenGLRenderer::createCommandList() const -> std::unique_ptr<ICommandList>
{
    return std::make_unique<OpenGLCommandList>();
}

auto OpenGLRenderer::createBuffer(const BufferDescriptor & descriptor) const -> std::unique_ptr<IBuffer>
{
    return std::make_unique<Buffer>(descriptor);
}

auto OpenGLRenderer::createFrameBuffer(const FrameBufferDescriptor & descriptor) const -> std::unique_ptr<IFrameBuffer>
{
    return std::make_unique<OpenGLFrameBuffer>(descriptor, *this);
}

auto OpenGLRenderer::createTexture(const TextureDescriptor & descriptor) const -> std::unique_ptr<ITexture>
{
    return std::make_unique<OpenGLTexture>(descriptor);
}

auto OpenGLRenderer::createDescriptorSet(const DescriptorSetDescriptor & descriptor) const -> std::unique_ptr<IDescriptorSet>
{
    return std::make_unique<OpenGLDescriptorSet>(descriptor);
}

auto OpenGLRenderer::createSampler(const SamplerDescriptor & descriptor) const -> std::unique_ptr<ISampler>
{
    return std::make_unique<OpenGLSampler>(descriptor);
}

auto OpenGLRenderer::createShader(const ShaderDescriptor & descriptor) const -> std::unique_ptr<IShader>
{
    return std::make_unique<OpenGLShader>(descriptor);
}

auto OpenGLRenderer::getUploadContext() const -> const IUploadContext &
{
    return m_uploadContext;
}

} // namespace ProtonEngine::Renderer::OpenGL
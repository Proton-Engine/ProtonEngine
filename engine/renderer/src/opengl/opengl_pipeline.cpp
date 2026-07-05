/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_pipeline.h"

#include <glad/gl.h>
#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

namespace
{

[[nodiscard]] auto toGLType(VertexFormat format) -> int32_t
{
    switch (format)
    {
    case VertexFormat::Float2: return GL_FLOAT;
    case VertexFormat::Float3: return GL_FLOAT;
    }

    throw std::runtime_error("Invalid vertex format");
}

[[nodiscard]] auto sizeOf(VertexFormat format) -> int32_t
{
    switch (format)
    {
    case VertexFormat::Float2: return 2;
    case VertexFormat::Float3: return 3;
    }

    throw std::runtime_error("Invalid vertex format");
}

void validatePipelineDescriptor(const PipelineDescriptor & descriptor, const std::unique_ptr<IShader> & shader)
{
    if (!shader)
    {
        throw std::runtime_error("Pipeline descriptor must have a shader");
    }

    if (descriptor.vertexAttributeDescriptor.attributes.empty())
    {
        throw std::runtime_error("Pipeline descriptor must have at least one vertex attribute");
    }

    for (const auto & vertexAttribute : descriptor.vertexAttributeDescriptor.attributes)
    {
        if (vertexAttribute.binding != 0)
        {
            // When we add support for multiple vertex attribute bindings, we will also have to make changes in
            // OpenGLCommandList to support different strides per binding
            throw std::runtime_error("Only vertex attribute binding 0 is supported");
        }
    }
}

} // namespace

OpenGLPipeline::OpenGLPipeline(PipelineDescriptor && descriptor) : m_shader(std::move(descriptor.shader)), m_stride(descriptor.vertexAttributeDescriptor.stride)
{
    validatePipelineDescriptor(descriptor, m_shader);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    for (const auto & vertexAttribute : descriptor.vertexAttributeDescriptor.attributes)
    {
        glEnableVertexAttribArray(vertexAttribute.location);
        glVertexAttribFormat(vertexAttribute.location, sizeOf(vertexAttribute.format), toGLType(vertexAttribute.format), GL_FALSE, vertexAttribute.offset);
        glVertexAttribBinding(vertexAttribute.location, vertexAttribute.binding);
    }
}

OpenGLPipeline::~OpenGLPipeline()
{
    glDeleteVertexArrays(1, &m_vao);
}

auto OpenGLPipeline::shader() const -> const OpenGLShader &
{
    return static_cast<const OpenGLShader &>(*m_shader);
}

auto OpenGLPipeline::stride() const -> uint32_t
{
    return m_stride;
}

auto OpenGLPipeline::vao() const -> uint32_t
{
    return m_vao;
}

} // namespace ProtonEngine::Renderer::OpenGL

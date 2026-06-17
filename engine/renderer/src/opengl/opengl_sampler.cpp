// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "opengl_sampler.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer::OpenGL
{

namespace
{

[[nodiscard]] auto scalingModeToGlMode(const ScalingMode mode) -> GLenum
{
    switch (mode)
    {
    case ScalingMode::LINEAR:
        return GL_LINEAR;
    case ScalingMode::NEAREST:
        return GL_NEAREST;
    }
    throw std::runtime_error("Invalid scaling mode, should never be reached");
}

[[nodiscard]] auto wrappingModeToGlMode(const WrappingMode mode) -> GLenum
{
    switch (mode)
    {
    case WrappingMode::REPEAT:
        return GL_REPEAT;
    case WrappingMode::CLAMP_TO_EDGE:
        return GL_CLAMP_TO_EDGE;
    }
    throw std::runtime_error("Invalid wrapping mode, should never be reached");
}

} // namespace

OpenGLSampler::OpenGLSampler(const SamplerDescriptor & descriptor) : m_descriptor(descriptor)
{
    glGenSamplers(1, &m_samplerId);

    const auto scalingOpenglMode = scalingModeToGlMode(descriptor.scalingMode);
    const auto wrappingOpenglMode = wrappingModeToGlMode(descriptor.wrappingMode);

    glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, scalingOpenglMode);
    glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, scalingOpenglMode);

    glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_S, wrappingOpenglMode);
    glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_T, wrappingOpenglMode);
    glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_R, wrappingOpenglMode);
}

OpenGLSampler::~OpenGLSampler()
{
    glDeleteSamplers(1, &m_samplerId);
}

void OpenGLSampler::bind(uint32_t slot) const
{
    glBindSampler(slot, m_samplerId);
}

} // namespace ProtonEngine::Renderer::OpenGL

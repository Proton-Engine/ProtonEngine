/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_shader.h"

#include "protonengine/common/logger.h"

#include <glad/gl.h>
#include <print>
#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

namespace
{

[[nodiscard]] auto toOpenGlSource(ShaderType type)
{
    switch (type)
    {
    case ShaderType::Vertex:
        return GL_VERTEX_SHADER;
    case ShaderType::Fragment:
        return GL_FRAGMENT_SHADER;
    }
    throw std::runtime_error("Invalid shader type");
}

[[nodiscard]] auto getErrorFromShaderCompilation(uint32_t shaderId) -> std::string
{
    int InfoLogLength;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength, ' ');
    glGetShaderInfoLog(shaderId, InfoLogLength, nullptr, error.data());

    return error;
}

[[nodiscard]] auto getErrorFromProgramLinking(uint32_t programId) -> std::string
{
    int InfoLogLength;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength, ' ');
    glGetProgramInfoLog(programId, InfoLogLength, nullptr, error.data());

    return error;
}

[[nodiscard]] auto compileShader(const std::string & source, ShaderType type) -> uint32_t
{
    uint32_t shaderId = glCreateShader(toOpenGlSource(type));
    const auto * shaderSource = source.c_str();
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    auto result = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result != GL_TRUE)
    {
        const auto error = getErrorFromShaderCompilation(shaderId);
        PROTON_LOG_ERROR(error);
        throw std::runtime_error("Failed to compile shader");
    }

    return shaderId;
}

} // namespace

OpenGLShader::OpenGLShader(const ShaderDescriptor & descriptor)
    : m_descriptor(descriptor)
{
    m_programId = glCreateProgram();

    for (const auto & sourceDescriptor : descriptor.sources)
    {
        const auto shader = compileShader(sourceDescriptor.source, sourceDescriptor.type);
        glAttachShader(m_programId, shader);
        m_shaderIds.emplace_back(shader);
    }

    glLinkProgram(m_programId);
    int result;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &result);

    if (result != GL_TRUE)
    {
        const auto error = getErrorFromProgramLinking(m_programId);
        PROTON_LOG_ERROR(std::format("Linking shader {} gave the following error: {}", m_descriptor.name, error));
        throw std::runtime_error("Failed to link shader");
    }

    PROTON_LOG_INFO(std::format("Succesfully compiled shader: {}", m_descriptor.name));
}

OpenGLShader::~OpenGLShader()
{
    for (const auto shaderId : m_shaderIds)
    {
        glDetachShader(m_programId, shaderId);
        glDeleteShader(shaderId);
    }

    glDeleteProgram(m_programId);
}

void OpenGLShader::enable() const noexcept
{
    glUseProgram(m_programId);
}

void OpenGLShader::disable() const noexcept
{
    glUseProgram(0);
}

auto OpenGLShader::programId() const noexcept -> uint32_t
{
    return m_programId;
}

} // namespace ProtonEngine::Renderer::OpenGL
/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/shader_program.h"

#include <glad/gl.h>
#include <fmt/core.h>

#include <fstream>
#include <sstream>

namespace ProtonEngine::Renderer {

[[nodiscard]] static GLint loadShader(std::string_view filename, ShaderType type);
[[nodiscard]] static std::string getErrorFromShaderCompilation(uint32_t shaderId);
[[nodiscard]] static std::string getErrorFromProgramLinking(uint32_t programId);
[[nodiscard]] static std::string loadShaderSourceFromDisk(std::string_view fileName);

enum class ShaderType
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

ShaderProgram::ShaderProgram(std::string_view shaderName)
    : m_name(shaderName)
{
    m_shaderProgramID = glCreateProgram();

    m_vertexShaderID = loadShader(fmt::format("./assets/shaders/{}.vertex", shaderName), ShaderType::Vertex);
    m_fragmentShaderID = loadShader(fmt::format("./assets/shaders/{}.fragment", shaderName), ShaderType::Fragment);

    glAttachShader(m_shaderProgramID, m_vertexShaderID);
    glAttachShader(m_shaderProgramID, m_fragmentShaderID);
    glLinkProgram(m_shaderProgramID);

    int result;
    glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &result);

    if(result != GL_TRUE)
    {
        const auto error = getErrorFromProgramLinking(m_shaderProgramID);
        fmt::print("{}\n", error);
    }
}

ShaderProgram::~ShaderProgram() noexcept
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);

    glDeleteProgram(m_shaderProgramID);
}

void ShaderProgram::enable() const noexcept
{
    glUseProgram(m_shaderProgramID);
}

void ShaderProgram::disable() const noexcept
{
    glUseProgram(0);
}

std::string_view ShaderProgram::name() noexcept
{
    return m_name;
}

[[nodiscard]] GLint loadShader(std::string_view fileName, ShaderType type)
{
    auto shaderId = glCreateShader(static_cast<int>(type));
    auto result = GL_FALSE;

    const auto source = loadShaderSourceFromDisk(fileName);
    char const * vertexSourcePointer = source.data();
    glShaderSource(shaderId, 1, &vertexSourcePointer , nullptr);
    glCompileShader(shaderId);

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if(result != GL_TRUE)
    {
        const auto error = getErrorFromShaderCompilation(shaderId);
        fmt::print("{}\n", error);
    }

    return shaderId;
}

[[nodiscard]] std::string getErrorFromShaderCompilation(uint32_t shaderId)
{
    int InfoLogLength;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength + 1, ' ');
    glGetShaderInfoLog(shaderId, InfoLogLength, nullptr, error.data());

    return error;
}

[[nodiscard]] std::string getErrorFromProgramLinking(uint32_t programId)
{
    int InfoLogLength;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength + 1, ' ');
    glGetProgramInfoLog(programId, InfoLogLength, nullptr, error.data());

    return error;
}

[[nodiscard]] std::string loadShaderSourceFromDisk(std::string_view fileName)
{
    std::ifstream fileStream(fileName);
    std::stringstream shaderSource;
    std::string line;

    while(std::getline(fileStream, line))
    {
        shaderSource << line << "\n";
    }

    return shaderSource.str();
}

}
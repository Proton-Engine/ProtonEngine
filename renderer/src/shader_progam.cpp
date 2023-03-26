/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/shader_program.h"

#include <glad/gl.h>
#include <fmt/core.h>

namespace ProtonEngine::Renderer {

enum class ShaderType
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};

ShaderProgram::ShaderProgram(std::string_view shaderName)
    : m_name(shaderName)
{
    m_shaderProgramID = glCreateProgram();

    std::string vertexShaderCode = "#version 330 core\n"
                                   "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
                                   "\n"
                                   "void main(){\n"
                                   "  gl_Position.xyz = vertexPosition_modelspace;\n"
                                   "  gl_Position.w = 1.0;\n"
                                   "}";
    m_vertexShaderID = loadShader(vertexShaderCode, ShaderType::Vertex);

    std::string fragmentShaderCode = "#version 330 core\n"
                                     "out vec3 color;\n"
                                     "\n"
                                     "void main(){\n"
                                     "  color = vec3(1,1,0);\n"
                                     "}";
    m_fragmentShaderID = loadShader(fragmentShaderCode, ShaderType::Fragment);

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

ShaderProgram::~ShaderProgram()
{
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);

    glDeleteProgram(m_shaderProgramID);
}

void ShaderProgram::enable()
{
    glUseProgram(m_shaderProgramID);
}

void ShaderProgram::disable()
{
    glUseProgram(0);
}

std::string_view ShaderProgram::name() noexcept
{
    return m_name;
}

uint32_t ShaderProgram::loadShader(std::string_view source, ShaderType type)
{
    auto shaderId = glCreateShader(static_cast<int>(type));
    auto result = GL_FALSE;

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

std::string ShaderProgram::getErrorFromShaderCompilation(uint32_t shaderId)
{
    int InfoLogLength;

    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength + 1, ' ');
    glGetShaderInfoLog(shaderId, InfoLogLength, nullptr, error.data());

    return error;
}

std::string ShaderProgram::getErrorFromProgramLinking(uint32_t programId)
{
    int InfoLogLength;

    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::string error(InfoLogLength + 1, ' ');
    glGetProgramInfoLog(programId, InfoLogLength, nullptr, error.data());

    return error;
}

}
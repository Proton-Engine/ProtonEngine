/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <inttypes.h>
#include <string>
#include <string_view>

namespace ProtonEngine::Renderer {

enum class ShaderType;

class ShaderProgram
{
public:
    explicit ShaderProgram(std::string_view shaderName);
    ~ShaderProgram() noexcept;
    ShaderProgram(const ShaderProgram & other) = delete;
    ShaderProgram& operator =(const ShaderProgram & other) = delete;
    ShaderProgram(ShaderProgram && other) noexcept = default;
    ShaderProgram& operator =(ShaderProgram && other) = default;

    void enable() const noexcept;
    void disable() const noexcept;

    [[nodiscard]] std::string_view name() noexcept;

private:
    std::string m_name;

    uint32_t m_shaderProgramID;
    uint32_t m_vertexShaderID;
    uint32_t m_fragmentShaderID;
};

}
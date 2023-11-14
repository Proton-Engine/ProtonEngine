/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <glm/mat4x4.hpp>

#include <cinttypes>
#include <string>
#include <string_view>

namespace ProtonEngine::Renderer {

enum class ShaderType;

class PROTON_API ShaderProgram
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

    void setUniformValue(std::string_view name, glm::mat4 matrix) noexcept;

    [[nodiscard]] std::string_view name() noexcept;

private:
    std::string m_name;

    uint32_t m_shaderProgramID;
    uint32_t m_vertexShaderID;
    uint32_t m_fragmentShaderID;
};

}
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"

#include <glm/mat4x4.hpp>

#include <string>
#include <string_view>

namespace ProtonEngine::Renderer::OpenGL
{

enum class ShaderType;

class ShaderProgram
{
public:
    explicit ShaderProgram(std::string_view shaderName);
    ~ShaderProgram() noexcept;
    ShaderProgram(const ShaderProgram & other) = delete;
    ShaderProgram & operator=(const ShaderProgram & other) = delete;
    ShaderProgram(ShaderProgram && other) noexcept = default;
    ShaderProgram & operator=(ShaderProgram && other) = default;

    void enable() const noexcept;
    void disable() const noexcept;

    void setUniformValue(std::string_view name, glm::vec3 vector) noexcept;
    void setUniformValue(std::string_view name, glm::mat4 matrix) noexcept;

    [[nodiscard]] std::string_view name() noexcept;

private:
    std::string m_name;

    uint32_t m_shaderProgramID;
    uint32_t m_vertexShaderID;
    uint32_t m_fragmentShaderID;
};

} // namespace ProtonEngine::Renderer::OpenGL
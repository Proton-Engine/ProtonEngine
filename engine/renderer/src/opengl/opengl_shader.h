/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ishader.h"

#include <glm/fwd.hpp>

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLShader : public IShader
{
public:
    OpenGLShader(const ShaderDescriptor & descriptor);
    ~OpenGLShader() override;
    OpenGLShader(OpenGLShader &) = delete;
    OpenGLShader(OpenGLShader &&) = delete;
    OpenGLShader & operator=(OpenGLShader &) = delete;
    OpenGLShader & operator=(OpenGLShader &&) = delete;

    void enable() const noexcept;
    void disable() const noexcept;

    [[nodiscard]] auto programId() const noexcept -> uint32_t;

private:
    ShaderDescriptor m_descriptor;

    uint32_t m_programId;
    std::vector<uint32_t> m_shaderIds;
};

} // namespace ProtonEngine::Renderer::OpenGL
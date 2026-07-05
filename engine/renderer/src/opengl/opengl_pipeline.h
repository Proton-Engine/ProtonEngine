/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ipipeline.h"

#include "opengl_shader.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLPipeline : public IPipeline
{
public:
    explicit OpenGLPipeline(PipelineDescriptor && descriptor);
    ~OpenGLPipeline() override;

    [[nodiscard]] auto shader() const -> const OpenGLShader &;
    [[nodiscard]] auto stride() const -> uint32_t;
    [[nodiscard]] auto vao() const -> uint32_t;

private:
    std::unique_ptr<IShader> m_shader;
    uint32_t m_stride{};
    uint32_t m_vao{};
};

} // namespace ProtonEngine::Renderer::OpenGL

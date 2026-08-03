/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/iframe_buffer.h"

#include "opengl_renderer.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLFrameBuffer : public IFrameBuffer
{
public:
    explicit OpenGLFrameBuffer(const FrameBufferDescriptor & descriptor, const OpenGLRenderer & renderBackend);
    ~OpenGLFrameBuffer() override;


    [[nodiscard]] auto bufferSize() const noexcept -> glm::u32vec2 override;
    [[nodiscard]] auto colorTexture() const noexcept -> const ITexture & override;

    [[nodiscard]] auto id() const -> uint32_t;

private:
    FrameBufferDescriptor m_descriptor;

    uint32_t m_frameBufferId{};
    uint32_t m_renderBufferId{};

    std::unique_ptr<ITexture> m_colorTexture;
    std::unique_ptr<ITexture> m_depthStencilTexture;
};

} // namespace ProtonEngine::Renderer::OpenGL

// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/itexture.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLTexture : public ITexture
{
public:
    explicit OpenGLTexture(const TextureDescriptor & descriptor);

    [[nodiscard]] auto getDescriptor() const -> TextureDescriptor override;
    void bind(uint32_t slot) const noexcept override;
    void unbind(uint32_t slot) const noexcept override;

    [[nodiscard]] auto getDataFormat() const noexcept -> uint32_t;
    [[nodiscard]] auto getInternalDataFormat() const noexcept -> uint32_t;

private:
    uint32_t m_textureID{};
    uint32_t m_dataFormat{};
    uint32_t m_internalDataFormat{};
    TextureDescriptor m_descriptor{};
};

} // namespace ProtonEngine::Renderer::OpenGL
/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <cstdint>

namespace ProtonEngine::Renderer
{

enum class TextureFormat
{
    RGB8,
    RGBA8,
    DEPTH_STENCIL
};

struct TextureDescriptor
{
    uint32_t width;
    uint32_t height;

    TextureFormat format;
};

class ITexture
{
public:
    ITexture() = default;
    virtual ~ITexture() = default;
    ITexture(ITexture &) = delete;
    ITexture(ITexture &&) = delete;
    ITexture & operator=(ITexture &) = delete;
    ITexture & operator=(ITexture &&) = delete;

    [[nodiscard]] virtual auto getDescriptor() const -> TextureDescriptor = 0;
    // TODO: This shouldn't be here!
    [[nodiscard]] virtual auto id() const noexcept -> uint32_t = 0;
};

} // namespace ProtonEngine::Renderer
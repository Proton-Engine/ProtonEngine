// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include <cstdint>

namespace ProtonEngine::Renderer
{

enum class TextureFormat
{
    RGB8,
    RGBA8,
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
    virtual void bind(uint32_t slot) const noexcept = 0;
    virtual void unbind(uint32_t slot) const noexcept = 0;
    // virtual void bind(uint32_t slot) const = 0;
};

} // namespace ProtonEngine::Renderer
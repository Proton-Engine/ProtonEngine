/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "itexture.h"

#include <glm/vec2.hpp>

#include <cstdint>

namespace ProtonEngine::Renderer
{

// enum class FrameBufferAttachment
// {
//     COLOR,
//     DEPTH,
//     STENCIL,
// };

struct FrameBufferDescriptor
{
    uint32_t width;
    uint32_t height;
    // std::unordered_set<FrameBufferAttachment> attachments;
};

class IFrameBuffer
{
public:
    IFrameBuffer() = default;
    virtual ~IFrameBuffer() = default;
    IFrameBuffer(const IFrameBuffer &) = delete;
    IFrameBuffer & operator=(const IFrameBuffer &) = delete;
    IFrameBuffer(IFrameBuffer &&) = default;
    IFrameBuffer & operator=(IFrameBuffer &&) = default;

    [[nodiscard]] virtual auto bufferSize() const noexcept -> glm::u32vec2 = 0;
    [[nodiscard]] virtual auto colorTexture() const noexcept -> const ITexture & = 0;
};

} // namespace ProtonEngine::Renderer

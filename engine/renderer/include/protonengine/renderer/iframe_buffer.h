/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "itexture.h"

#include <cstdint>
#include <memory>
#include <unordered_set>

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
    IFrameBuffer(IFrameBuffer &&) = delete;
    IFrameBuffer & operator=(IFrameBuffer &&) = delete;

    virtual auto colorTexture() -> const ITexture & = 0;
};

} // namespace ProtonEngine::Renderer

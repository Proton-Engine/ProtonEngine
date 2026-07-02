/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "vertex.h"

#include <vector>

namespace ProtonEngine::Renderer
{

enum class BufferType
{
    VERTEX,
    INDEX,
    UNIFORM
};

struct BufferDescriptor
{
    BufferType type;
};

class IBuffer
{
public:
    IBuffer() = default;
    virtual ~IBuffer() = default;
    IBuffer(const IBuffer &) = delete;
    IBuffer & operator=(const IBuffer &) = delete;
    IBuffer(IBuffer &&) = default;
    IBuffer & operator=(IBuffer &&) = default;

    virtual void bind() const noexcept = 0;
    virtual void unbind() const noexcept = 0;
    // [[nodiscard]] virtual int32_t verticesCount() const noexcept = 0;
    // [[nodiscard]] virtual int32_t indicesCount() const noexcept = 0;
};

} // namespace ProtonEngine::Renderer

/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/vertex.h"

#include <span>
#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class Buffer : public IBuffer
{
public:
    Buffer(const BufferDescriptor & descriptor);
    ~Buffer() override;

    void bind() const noexcept;
    void unbind() const noexcept;

    // TODO: Remove const
    void setData(std::span<const std::byte> data) const;
    [[nodiscard]] auto id() const noexcept -> uint32_t;

private:
    uint32_t m_bufferHandle{};
    int32_t m_bindType;
    BufferDescriptor m_descriptor{};
};

} // namespace ProtonEngine::Renderer::OpenGL

/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/vertex.h"

namespace ProtonEngine::Renderer::OpenGL
{

class Buffer : public IBuffer
{
public:
    Buffer(const BufferDescriptor & descriptor);
    ~Buffer() override;

    [[nodiscard]] auto id() const noexcept -> uint32_t;
    [[nodiscard]] auto bindType() const noexcept -> int32_t;

private:
    uint32_t m_bufferHandle{};
    int32_t m_bindType;
    BufferDescriptor m_descriptor{};
};

} // namespace ProtonEngine::Renderer::OpenGL

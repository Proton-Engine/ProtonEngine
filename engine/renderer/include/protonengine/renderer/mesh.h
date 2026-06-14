/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"
#include "protonengine/renderer/ibuffer.h"

#include <cinttypes>
#include <memory>

namespace ProtonEngine::Renderer
{

class PROTONENGINE_RENDERER_EXPORT Mesh
{
public:
    explicit Mesh(std::unique_ptr<IBuffer> vertexBuffer, std::unique_ptr<IBuffer> indexBuffer, size_t indicesCount);
    ~Mesh() = default;

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    // [[nodiscard]] int32_t verticesCount() const noexcept;
    // [[nodiscard]] int32_t indicesCount() const noexcept;

    [[nodiscard]] auto vertexBuffer() const noexcept -> const IBuffer &;
    [[nodiscard]] auto indexBuffer() const noexcept -> const IBuffer &;
    [[nodiscard]] auto indicesCount() const noexcept -> const size_t;

private:
    std::unique_ptr<IBuffer> m_vertexBuffer;
    std::unique_ptr<IBuffer> m_indexBuffer;
    size_t m_indicesCount;
};

} // namespace ProtonEngine::Renderer
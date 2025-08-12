/*
 * Copyright © 2022-2025. Proton Engine
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
    explicit Mesh(std::unique_ptr<IBuffer> buffer);
    ~Mesh() = default;

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    [[nodiscard]] int32_t verticesCount() const noexcept;
    [[nodiscard]] int32_t indicesCount() const noexcept;

private:
    std::unique_ptr<IBuffer> m_buffer;
};

} // namespace ProtonEngine::Renderer
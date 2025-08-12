/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"
#include "vertex.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer
{

class PROTONENGINE_RENDERER_EXPORT Mesh
{
public:
    explicit Mesh(const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices);
    ~Mesh();

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    [[nodiscard]] int32_t verticesCount() const noexcept;
    [[nodiscard]] int32_t indicesCount() const noexcept;

private:
    // TODO: Remove these ID's :D
    uint32_t m_vertexArrayObject{};
    uint32_t m_vertexBufferObject{};
    uint32_t m_indexBufferObject{};
    int32_t m_verticesCount{};
    int32_t m_indicesCount{};
};

} // namespace ProtonEngine::Renderer
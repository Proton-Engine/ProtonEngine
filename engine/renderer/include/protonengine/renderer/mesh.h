/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer
{

class PROTONENGINE_RENDERER_EXPORT Mesh
{
public:
    Mesh(const std::vector<float> & meshData, const std::vector<float> & normals, const std::vector<float> & textureCoordinates);
    ~Mesh();

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    [[nodiscard]] int32_t verticesCount() const noexcept;

private:
    uint32_t m_vertexArrayId{};
    uint32_t m_vertexBufferId{};
    uint32_t m_normalBufferId{};
    uint32_t m_textureBufferId{};
    int32_t m_verticesCount{};
};

} // namespace ProtonEngine::Renderer
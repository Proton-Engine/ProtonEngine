// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/vertex.h"

#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class Buffer : public IBuffer
{
public:
    explicit Buffer(const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices);
    ~Buffer() override;

    void bind() const noexcept override;
    void unbind() const noexcept override;
    [[nodiscard]] int32_t verticesCount() const noexcept override;
    [[nodiscard]] int32_t indicesCount() const noexcept override;

private:
    uint32_t m_vertexArrayObject{};
    uint32_t m_vertexBufferObject{};
    uint32_t m_indexBufferObject{};
    int32_t m_verticesCount{};
    int32_t m_indicesCount{};
};

} // namespace ProtonEngine::Renderer::OpenGL

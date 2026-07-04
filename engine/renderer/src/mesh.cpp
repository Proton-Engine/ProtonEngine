/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include "protonengine/assets/model.h"
#include "protonengine/renderer/vertex.h"

namespace ProtonEngine::Renderer
{

Mesh::Mesh(std::unique_ptr<IBuffer> vertexBuffer, std::unique_ptr<IBuffer> indexBuffer, size_t indicesCount) :
    m_vertexBuffer(std::move(vertexBuffer)),
    m_indexBuffer(std::move(indexBuffer)),
    m_indicesCount(indicesCount)
{
}

auto Mesh::vertexBuffer() const noexcept -> const IBuffer &
{
    return *m_vertexBuffer;
}

auto Mesh::indexBuffer() const noexcept -> const IBuffer &
{
    return *m_indexBuffer;
}

auto Mesh::indicesCount() const noexcept -> size_t
{
    return m_indicesCount;
}

} // namespace ProtonEngine::Renderer
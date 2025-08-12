/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include "protonengine/assets/model.h"
#include "protonengine/renderer/vertex.h"

namespace ProtonEngine::Renderer
{

Mesh::Mesh(std::unique_ptr<IBuffer> buffer) :
    m_buffer(std::move(buffer))
{
}

void Mesh::enableForDrawing() const noexcept
{
    m_buffer->bind();
}

void Mesh::disableForDrawing() const noexcept
{
    m_buffer->unbind();
}

int32_t Mesh::verticesCount() const noexcept
{
    return m_buffer->verticesCount();
}

int32_t Mesh::indicesCount() const noexcept
{
    return m_buffer->indicesCount();
}

} // namespace ProtonEngine::Renderer
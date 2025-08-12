/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include "glad/glad.h"
#include "protonengine/assets/model.h"
#include "protonengine/renderer/vertex.h"

namespace ProtonEngine::Renderer
{

Mesh::Mesh(const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices)
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glGenBuffers(1, &m_indexBufferObject);

    glBindVertexArray(m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, static_cast<int64_t>(vertices.size() * sizeof(Vertex)), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texture)));

    glBindVertexArray(0);

    m_verticesCount = static_cast<int32_t>(vertices.size());
    m_indicesCount = static_cast<int32_t>(indices.size());
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::enableForDrawing() const noexcept
{
    glBindVertexArray(m_vertexArrayObject);
}

void Mesh::disableForDrawing() const noexcept
{
    glBindVertexArray(0);
}

int32_t Mesh::verticesCount() const noexcept
{
    return m_verticesCount;
}

int32_t Mesh::indicesCount() const noexcept
{
    return m_indicesCount;
}

} // namespace ProtonEngine::Renderer
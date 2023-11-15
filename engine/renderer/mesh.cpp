/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include "glad/glad.h"

namespace ProtonEngine::Renderer {

Mesh::Mesh(const std::vector<float> & meshData, const std::vector<float> & normals, const std::vector<float> & textureCoordinates)
{
    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,0,nullptr);

    glGenBuffers(1, &m_normalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,0,nullptr);

    glGenBuffers(1, &m_textureBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferId);
    glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(float), textureCoordinates.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,0,nullptr);

    m_verticesCount = meshData.size();

}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Mesh::enableForDrawing() const noexcept
{
    glBindVertexArray(m_vertexArrayId);
}

void Mesh::disableForDrawing() const noexcept
{
    glBindVertexArray(0);
}

int32_t Mesh::verticesCount() const noexcept
{
    return m_verticesCount;
}

}
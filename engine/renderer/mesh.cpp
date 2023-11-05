/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include "glad/glad.h"

namespace ProtonEngine::Renderer {

Mesh::Mesh(const std::vector<float> & meshData, const std::vector<float> & textureCoordinates)
{
    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        nullptr             // array buffer offset
    );

    glGenBuffers(1, &m_textureBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferId);
    glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(float), textureCoordinates.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(
        1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        nullptr             // array buffer offset
    );

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
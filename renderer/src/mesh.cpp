/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/mesh.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer {

Mesh::Mesh(const std::vector<float> & meshData)
{
    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);

    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, meshData.size() * sizeof(float), meshData.data(), GL_STATIC_DRAW);

    m_verticesCount = meshData.size();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void Mesh::enableForDrawing() const noexcept
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);

    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
}

void Mesh::disableForDrawing() const noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
}

uint32_t Mesh::vertices() const noexcept
{
    return m_verticesCount;
}

}
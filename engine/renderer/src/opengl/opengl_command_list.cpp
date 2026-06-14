// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "opengl_command_list.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer::OpenGL
{

OpenGLCommandList::OpenGLCommandList()
{
    glGenVertexArrays(1, &m_vao);
}

void OpenGLCommandList::begin()
{
    // Handle state?
}

void OpenGLCommandList::end()
{
    // Handle state?
}

void OpenGLCommandList::setPipeline()
{
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, position)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texture)));
}

void OpenGLCommandList::setVertexBuffer(const IBuffer & buffer)
{
    buffer.bind();
}

void OpenGLCommandList::setIndexBuffer(const IBuffer & buffer)
{
    buffer.bind();
}

void OpenGLCommandList::drawIndexed(uint32_t indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

} // namespace ProtonEngine::Renderer::OpenGL
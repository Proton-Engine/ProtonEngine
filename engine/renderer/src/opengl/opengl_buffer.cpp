/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_buffer.h"

#include <glad/gl.h>

namespace ProtonEngine::Renderer::OpenGL
{

Buffer::Buffer(const BufferDescriptor & descriptor) : m_descriptor(descriptor)
{
    glGenBuffers(1, &m_bufferHandle);

    m_bindType = [&] {
        switch (m_descriptor.type)
        {
        case BufferType::VERTEX: return GL_ARRAY_BUFFER;
        case BufferType::INDEX: return GL_ELEMENT_ARRAY_BUFFER;
        }
        throw "Should never ever be reached!";
    }();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_bufferHandle);
}

void Buffer::bind() const noexcept
{
    glBindBuffer(m_bindType, m_bufferHandle);
}

void Buffer::unbind() const noexcept
{
    glBindBuffer(m_bindType, 0);
}

void Buffer::setData(std::span<const std::byte> data) const
{
    glBufferData(m_bindType, data.size(), data.data(), GL_STATIC_DRAW);
}

} // namespace ProtonEngine::Renderer::OpenGL
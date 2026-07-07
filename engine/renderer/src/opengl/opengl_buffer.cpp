/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_buffer.h"

#include <glad/gl.h>
#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

Buffer::Buffer(const BufferDescriptor & descriptor)
    : m_descriptor(descriptor)
{
    glGenBuffers(1, &m_bufferHandle);

    m_bindType = [&] {
        switch (m_descriptor.type)
        {
        case BufferType::VERTEX: return GL_ARRAY_BUFFER;
        case BufferType::INDEX: return GL_ELEMENT_ARRAY_BUFFER;
        case BufferType::UNIFORM: return GL_UNIFORM_BUFFER;
        }
        throw std::runtime_error("Should never ever be reached!");
    }();
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_bufferHandle);
}

auto Buffer::id() const noexcept -> uint32_t
{
    return m_bufferHandle;
}

auto Buffer::bindType() const noexcept -> int32_t
{
    return m_bindType;
}

} // namespace ProtonEngine::Renderer::OpenGL
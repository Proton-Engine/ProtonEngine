// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "opengl_command_list.h"

#include "opengl_buffer.h"
#include "opengl_descriptor_set.h"
#include "opengl_sampler.h"
#include "protonengine/common/logger.h"

#include <glad/gl.h>

#include <format>

namespace ProtonEngine::Renderer::OpenGL
{

namespace
{

constexpr std::array g_uniformBufferNames = {
    "ModelDataBuffer",
    "ViewDataBuffer",
    "MaterialBuffer",
    "LightsBuffer"};

} // namespace

// TODO: Remove this from here
extern uint32_t program;

OpenGLCommandList::OpenGLCommandList()
{
    glGenVertexArrays(1, &m_vao);
}

void OpenGLCommandList::begin()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void OpenGLCommandList::bindUniformBuffer(uint32_t slot, const IBuffer & buffer)
{
    const auto bufferId = static_cast<const OpenGL::Buffer *>(&buffer)->id();
    const auto blockIndex = glGetUniformBlockIndex(program, g_uniformBufferNames[slot]);

    if (blockIndex == GL_INVALID_INDEX)
    {
        PROTON_LOG_ERROR(std::format("Failed to get block index for name {}", g_uniformBufferNames[slot]));
    }

    glUniformBlockBinding(program, blockIndex, slot);
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, bufferId);
}

void OpenGLCommandList::drawIndexed(uint32_t indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void OpenGLCommandList::bindDescriptorSet(const IDescriptorSet & descriptorSet)
{
    const auto & openglDescriptorSet = static_cast<const OpenGLDescriptorSet &>(descriptorSet);
    const auto & textures = openglDescriptorSet.textures();
    const auto & samplers = openglDescriptorSet.samplers();

    for (const auto & buffer : openglDescriptorSet.buffers())
    {
        bindUniformBuffer(buffer.binding, buffer.buffer);
    }

    for (const auto & texture : textures)
    {
        texture.texture.bind(texture.binding);
    }

    for (const auto & sampler : samplers)
    {
        const auto & openGlSampler = static_cast<const OpenGLSampler &>(sampler.sampler);
        openGlSampler.bind(sampler.binding);
    }
}

} // namespace ProtonEngine::Renderer::OpenGL
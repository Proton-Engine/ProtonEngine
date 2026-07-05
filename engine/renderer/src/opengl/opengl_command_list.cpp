/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_command_list.h"

#include "opengl_buffer.h"
#include "opengl_descriptor_set.h"
#include "opengl_sampler.h"
#include "opengl_shader.h"
#include "protonengine/common/logger.h"

#include <glad/gl.h>

#include <array>
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

OpenGLCommandList::OpenGLCommandList()
{
    glGenVertexArrays(1, &m_vao);
}

OpenGLCommandList::~OpenGLCommandList()
{
    glDeleteVertexArrays(1, &m_vao);
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

void OpenGLCommandList::setPipeline(const Pipeline & pipeline)
{
    const auto openglShader = static_cast<const OpenGLShader *>(pipeline.shader.get());
    openglShader->enable();
    m_shaderProgram = openglShader->programId();

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexAttribBinding(0, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    glVertexAttribBinding(1, 0);

    glEnableVertexAttribArray(2);
    glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture));
    glVertexAttribBinding(2, 0);
}

void OpenGLCommandList::setVertexBuffer(const IBuffer & buffer)
{
    const auto bufferHandle = static_cast<const OpenGL::Buffer *>(&buffer)->id();
    glBindVertexBuffer(0, bufferHandle, 0, sizeof(Vertex));
}

void OpenGLCommandList::setIndexBuffer(const IBuffer & buffer)
{
    static_cast<const OpenGL::Buffer *>(&buffer)->bind();
}

void OpenGLCommandList::bindUniformBuffer(uint32_t slot, const IBuffer & buffer)
{
    const auto bufferId = static_cast<const OpenGL::Buffer *>(&buffer)->id();
    const auto blockIndex = glGetUniformBlockIndex(m_shaderProgram, g_uniformBufferNames.at(slot));

    if (blockIndex == GL_INVALID_INDEX)
    {
        PROTON_LOG_ERROR(std::format("Failed to get block index for name {}", g_uniformBufferNames[slot]));
        throw std::runtime_error(std::format("Failed to get block index for name {}", g_uniformBufferNames[slot]));
    }

    glUniformBlockBinding(m_shaderProgram, blockIndex, slot);
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
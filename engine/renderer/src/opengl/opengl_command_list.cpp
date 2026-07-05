/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_command_list.h"

#include "opengl_buffer.h"
#include "opengl_descriptor_set.h"
#include "opengl_pipeline.h"
#include "opengl_sampler.h"
#include "opengl_shader.h"
#include "protonengine/common/logger.h"

#include <glad/gl.h>

#include <array>
#include <format>
#include <stdexcept>

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

void OpenGLCommandList::begin()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Handle state?
}

void OpenGLCommandList::end()
{
    // Handle state?
}

void OpenGLCommandList::setPipeline(const IPipeline & pipeline)
{
    const auto & openglPipeline = static_cast<const OpenGLPipeline &>(pipeline);
    openglPipeline.shader().enable();
    m_shaderProgram = openglPipeline.shader().programId();
    vertexStride = openglPipeline.stride();

    glBindVertexArray(openglPipeline.vao());
}

void OpenGLCommandList::setVertexBuffer(const IBuffer & buffer, uint32_t slot, uint32_t offset)
{
    if (slot != 0) [[unlikely]]
    {
        throw std::runtime_error("Only vertex attribute binding 0 is supported");
    }

    const auto bufferHandle = static_cast<const OpenGL::Buffer *>(&buffer)->id();
    glBindVertexBuffer(slot, bufferHandle, offset, vertexStride);
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
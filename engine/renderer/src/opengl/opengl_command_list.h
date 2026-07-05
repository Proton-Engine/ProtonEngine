/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/icommand_list.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLCommandList : public ICommandList
{
public:
    OpenGLCommandList() = default;
    ~OpenGLCommandList() override = default;

    void begin() override;
    void end() override;
    void setPipeline(const IPipeline & pipeline) override;
    void setVertexBuffer(const IBuffer & buffer, uint32_t slot, uint32_t offset) override;
    void setIndexBuffer(const IBuffer & buffer) override;
    void bindUniformBuffer(uint32_t slot, const IBuffer & buffer) override;
    void drawIndexed(uint32_t indexCount) override;
    void bindDescriptorSet(const IDescriptorSet & descriptorSet) override;

private:
    uint32_t m_shaderProgram{};
    uint32_t vertexStride{};
};

} // namespace ProtonEngine::Renderer::OpenGL

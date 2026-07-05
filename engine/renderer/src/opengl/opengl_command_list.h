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
    OpenGLCommandList();
    ~OpenGLCommandList() override;

    void begin() override;
    void end() override;
    void setPipeline(const Pipeline & pipeline) override;
    void setVertexBuffer(const IBuffer & buffer) override;
    void setIndexBuffer(const IBuffer & buffer) override;
    void bindUniformBuffer(uint32_t slot, const IBuffer & buffer) override;
    void drawIndexed(uint32_t indexCount) override;
    void bindDescriptorSet(const IDescriptorSet & descriptorSet) override;

private:
    uint32_t m_shaderProgram{};
    uint32_t m_vao{};
};

} // namespace ProtonEngine::Renderer::OpenGL

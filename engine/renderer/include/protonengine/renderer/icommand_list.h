// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once
#include "ibuffer.h"
#include "idescriptor_set.h"

namespace ProtonEngine::Renderer
{

class ICommandList
{
public:
    ICommandList() = default;
    virtual ~ICommandList() = default;
    ICommandList(ICommandList &) = delete;
    ICommandList(ICommandList &&) = delete;
    ICommandList & operator=(ICommandList &) = delete;
    ICommandList & operator=(ICommandList &&) = delete;

    virtual void begin() = 0;
    virtual void end() = 0;

    virtual void setPipeline() = 0;
    virtual void setVertexBuffer(const IBuffer & buffer) = 0;
    virtual void setIndexBuffer(const IBuffer & buffer) = 0;
    virtual void bindUniformBuffer(uint32_t slot, const IBuffer & buffer) = 0;
    virtual void drawIndexed(uint32_t indexCount) = 0;
    virtual void bindDescriptorSet(const IDescriptorSet & descriptorSet) = 0;

    // virtual void Draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
};

} // namespace ProtonEngine::Renderer

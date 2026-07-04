/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/pipeline.h"

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

    // TODO: Change with pipeline abstraction
    virtual void setPipeline(const Pipeline & pipeline) = 0;
    virtual void setVertexBuffer(const IBuffer & buffer) = 0;
    virtual void setIndexBuffer(const IBuffer & buffer) = 0;
    virtual void bindUniformBuffer(uint32_t slot, const IBuffer & buffer) = 0;
    virtual void drawIndexed(uint32_t indexCount) = 0;
    virtual void bindDescriptorSet(const IDescriptorSet & descriptorSet) = 0;

    // virtual void Draw(uint32_t vertexCount, uint32_t firstVertex = 0) = 0;
};

} // namespace ProtonEngine::Renderer

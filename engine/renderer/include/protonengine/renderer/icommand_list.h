/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/clear_mode.h"
#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/iframe_buffer.h"
#include "protonengine/renderer/ipipeline.h"

#include "glm/vec4.hpp"

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

    virtual void setPipeline(const IPipeline & pipeline) = 0;
    virtual void setClearColour(glm::vec4 colour) = 0;
    virtual void clear(ClearMode clearMode) = 0;
    virtual void setVertexBuffer(const IBuffer & buffer, uint32_t slot = 0, uint32_t offset = 0) = 0;
    virtual void setIndexBuffer(const IBuffer & buffer) = 0;
    virtual void bindUniformBuffer(uint32_t slot, const IBuffer & buffer) = 0;
    virtual void drawIndexed(uint32_t indexCount) = 0;
    virtual void bindDescriptorSet(const IDescriptorSet & descriptorSet) = 0;
    virtual void attachFrameBuffer(const IFrameBuffer & frameBuffer) = 0;
    virtual void attachDefaultRenderTarget() = 0;
};

} // namespace ProtonEngine::Renderer

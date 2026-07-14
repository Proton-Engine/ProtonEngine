/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "iframe_buffer.h"
#include "protonengine/renderer/icommand_list.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/ipipeline.h"
#include "protonengine/renderer/ishader.h"
#include "protonengine/renderer/iupload_context.h"
#include "protonengine/renderer/mesh.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void (*(*)(const char *))(void);

class IRenderBackend
{
public:
    IRenderBackend() = default;
    virtual ~IRenderBackend() = default;
    IRenderBackend(IRenderBackend &) = delete;
    IRenderBackend(IRenderBackend &&) = delete;
    IRenderBackend & operator=(IRenderBackend &) = delete;
    IRenderBackend & operator=(IRenderBackend &&) = delete;

    virtual void setWindowContext(ContextLoadFunction func) = 0;
    virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

    [[nodiscard]] virtual auto createCommandList() const -> std::unique_ptr<ICommandList> = 0;
    [[nodiscard]] virtual auto createPipeline(PipelineDescriptor && descriptor) const -> std::unique_ptr<IPipeline> = 0;
    [[nodiscard]] virtual auto createBuffer(const BufferDescriptor & descriptor) const -> std::unique_ptr<IBuffer> = 0;
    [[nodiscard]] virtual auto createFrameBuffer(const FrameBufferDescriptor & descriptor) const -> std::unique_ptr<IFrameBuffer> = 0;
    [[nodiscard]] virtual auto createTexture(const TextureDescriptor & descriptor) const -> std::unique_ptr<ITexture> = 0;
    [[nodiscard]] virtual auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) const -> std::unique_ptr<IDescriptorSet> = 0;
    [[nodiscard]] virtual auto createSampler(const SamplerDescriptor & descriptor) const -> std::unique_ptr<ISampler> = 0;
    [[nodiscard]] virtual auto createShader(const ShaderDescriptor & descriptor) const -> std::unique_ptr<IShader> = 0;

    [[nodiscard]] virtual auto getUploadContext() const -> const IUploadContext & = 0;
};

} // namespace ProtonEngine::Renderer

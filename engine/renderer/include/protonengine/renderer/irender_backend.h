/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/export.h"
#include "protonengine/renderer/icommand_list.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/ipipeline.h"
#include "protonengine/renderer/ishader.h"
#include "protonengine/renderer/iupload_context.h"
#include "protonengine/renderer/material.h"
#include "protonengine/renderer/mesh.h"

namespace ProtonEngine::Renderer
{

using ContextLoadFunction = void (*(*)(const char *))(void);

class PROTONENGINE_RENDERER_EXPORT IRenderBackend
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

    [[nodiscard]] virtual auto createCommandList() -> std::unique_ptr<ICommandList> = 0;
    [[nodiscard]] virtual auto createPipeline(PipelineDescriptor && descriptor) -> std::unique_ptr<IPipeline> = 0;
    [[nodiscard]] virtual auto createBuffer(const BufferDescriptor & descriptor) -> std::unique_ptr<IBuffer> = 0;
    [[nodiscard]] virtual auto createTexture(const TextureDescriptor & descriptor) -> std::unique_ptr<ITexture> = 0;
    [[nodiscard]] virtual auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) -> std::unique_ptr<IDescriptorSet> = 0;
    [[nodiscard]] virtual auto createSampler(const SamplerDescriptor & descriptor) -> std::unique_ptr<ISampler> = 0;
    [[nodiscard]] virtual auto createShader(const ShaderDescriptor & descriptor) -> std::unique_ptr<IShader> = 0;

    [[nodiscard]] virtual auto getUploadContext() -> IUploadContext & = 0;
};

} // namespace ProtonEngine::Renderer

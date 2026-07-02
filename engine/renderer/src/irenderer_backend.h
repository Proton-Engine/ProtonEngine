// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/export.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/irenderer.h"
#include "protonengine/renderer/iupload_context.h"
#include "protonengine/renderer/material.h"
#include "protonengine/renderer/mesh.h"

namespace ProtonEngine::Renderer
{

class PROTONENGINE_RENDERER_EXPORT IRendererBackend : public IRenderer
{
public:
    ~IRendererBackend() override = default;

    [[nodiscard]] virtual auto createBuffer(const BufferDescriptor & descriptor) -> std::unique_ptr<IBuffer> = 0;
    [[nodiscard]] virtual auto createTexture(const TextureDescriptor & descriptor) -> std::unique_ptr<ITexture> = 0;
    [[nodiscard]] virtual auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) -> std::unique_ptr<IDescriptorSet> = 0;
    [[nodiscard]] virtual auto createSampler(const SamplerDescriptor & descriptor) -> std::unique_ptr<ISampler> = 0;

    [[nodiscard]] virtual auto getUploadContext() -> IUploadContext & = 0;

protected:
    IRendererBackend() = default;
};

} // namespace ProtonEngine::Renderer
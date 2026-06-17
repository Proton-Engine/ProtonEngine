/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/model.h"
#include "protonengine/renderer/camera.h"
#include "protonengine/renderer/export.h"
#include "protonengine/renderer/idescriptor_set.h"
#include "protonengine/renderer/iupload_context.h"
#include "protonengine/renderer/light.h"
#include "protonengine/renderer/material.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/transform.h"

namespace ProtonEngine::Renderer
{

enum class RendererBackend
{
    OPENGL
};

using ContextLoadFunction = void (*(*)(const char *))(void);
// using ContextLoadFunction = void * (*)(const char * name);

class PROTONENGINE_RENDERER_EXPORT IRenderer
{
public:
    virtual ~IRenderer() = default;
    IRenderer(IRenderer &) = delete;
    IRenderer(IRenderer &&) = delete;
    IRenderer & operator=(IRenderer &) = delete;
    IRenderer & operator=(IRenderer &&) = delete;

    virtual void setWindowContext(ContextLoadFunction func) = 0;

    virtual void addToRenderQueue(const Transform & transform, const Mesh & mesh, const Material & material) = 0;
    virtual void addLight(const Transform & transform, const Light & light) = 0;
    virtual void renderAllInQueue() = 0;
    virtual void setCamera(const Transform & transform, const Camera & camera) = 0;
    virtual void update() = 0;

    [[nodiscard]] virtual auto createBuffer(const BufferDescriptor & descriptor) -> std::unique_ptr<IBuffer> = 0;
    [[nodiscard]] virtual auto createTexture(const TextureDescriptor & descriptor) -> std::unique_ptr<ITexture> = 0;
    [[nodiscard]] virtual auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) -> std::unique_ptr<IDescriptorSet> = 0;
    [[nodiscard]] virtual auto createSampler(const SamplerDescriptor & descriptor) -> std::unique_ptr<ISampler> = 0;


    [[nodiscard]] virtual auto getUploadContext() -> IUploadContext & = 0;

protected:
    IRenderer() = default;
};

[[nodiscard]] PROTONENGINE_RENDERER_EXPORT auto initializeRenderer(RendererBackend rendererBackend) -> IRenderer &;
[[nodiscard]] PROTONENGINE_RENDERER_EXPORT auto createTextureFromImage(const Assets::Image & image) -> std::unique_ptr<ITexture>;
[[nodiscard]] PROTONENGINE_RENDERER_EXPORT auto createMeshFromModel(const Assets::Model & model) -> Mesh;

} // namespace ProtonEngine::Renderer

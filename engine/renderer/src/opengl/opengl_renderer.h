/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "opengl_command_list.h"
#include "opengl_upload_context.h"
#include "protonengine/renderer/irenderer.h"

#include "renderable_light.h"
#include "renderable_object.h"

#include <glm/glm.hpp>

#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLRenderer : public IRenderer
{
public:
    ~OpenGLRenderer() override = default;

    void setWindowContext(ContextLoadFunction func) override;

    void addToRenderQueue(const Transform & transform, const Mesh & mesh, const Material & material) override;
    void addLight(const Transform & transform, const Light & light) override;
    void renderAllInQueue() override;
    void setCamera(const Transform & transform, const Camera & camera) override;
    void update() override;

    [[nodiscard]] auto createBuffer(const BufferDescriptor & descriptor) -> std::unique_ptr<IBuffer> override;
    [[nodiscard]] auto createTexture(const TextureDescriptor & descriptor) -> std::unique_ptr<ITexture> override;
    [[nodiscard]] auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) -> std::unique_ptr<IDescriptorSet> override;
    [[nodiscard]] auto createSampler(const SamplerDescriptor & descriptor) -> std::unique_ptr<ISampler> override;

    [[nodiscard]] auto getUploadContext() -> IUploadContext & override;

private:
    glm::mat4 projection{};
    glm::mat4 view{};

    std::vector<RenderableObject> m_renderableObjects;
    std::vector<RenderableLight> m_lights;

    OpenGLUploadContext m_uploadContext;
    std::unique_ptr<OpenGLCommandList> m_commandList;
};

} // namespace ProtonEngine::Renderer::OpenGL
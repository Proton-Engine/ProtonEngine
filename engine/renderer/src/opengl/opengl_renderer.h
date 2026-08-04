/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/irender_backend.h"

#include "opengl_command_list.h"
#include "opengl_upload_context.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLRenderer : public IRenderBackend
{
public:
    ~OpenGLRenderer() override = default;

    void setWindowContext(ContextLoadFunction func) override;
    void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    [[nodiscard]] auto createPipeline(PipelineDescriptor && descriptor) const -> std::unique_ptr<IPipeline> override;
    [[nodiscard]] auto createCommandList() const -> std::unique_ptr<ICommandList> override;
    [[nodiscard]] auto createBuffer(const BufferDescriptor & descriptor) const -> std::unique_ptr<IBuffer> override;
    [[nodiscard]] auto createFrameBuffer(const FrameBufferDescriptor & descriptor) const -> std::unique_ptr<IFrameBuffer> override;
    [[nodiscard]] auto createTexture(const TextureDescriptor & descriptor) const -> std::unique_ptr<ITexture> override;
    [[nodiscard]] auto createDescriptorSet(const DescriptorSetDescriptor & descriptor) const -> std::unique_ptr<IDescriptorSet> override;
    [[nodiscard]] auto createSampler(const SamplerDescriptor & descriptor) const -> std::unique_ptr<ISampler> override;
    [[nodiscard]] auto createShader(const ShaderDescriptor & descriptor) const -> std::unique_ptr<IShader> override;

    [[nodiscard]] auto getUploadContext() const -> const IUploadContext & override;

private:
    OpenGLUploadContext m_uploadContext;
};

} // namespace ProtonEngine::Renderer::OpenGL
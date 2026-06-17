// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once
#include "protonengine/renderer/idescriptor_set.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLDescriptorSet : public IDescriptorSet
{
public:
    explicit OpenGLDescriptorSet(const DescriptorSetDescriptor & descriptor);
    ~OpenGLDescriptorSet() override = default;

    [[nodiscard]] auto textures() const noexcept -> const std::vector<TextureBinding> &;
    [[nodiscard]] auto samplers() const noexcept -> const std::vector<SamplerBinding> &;

private:
    std::vector<TextureBinding> m_textureBindings;
    std::vector<SamplerBinding> m_samplerBindings;
};

} // namespace ProtonEngine::Renderer::OpenGL

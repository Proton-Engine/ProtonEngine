// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "opengl_descriptor_set.h"

namespace ProtonEngine::Renderer::OpenGL
{

OpenGLDescriptorSet::OpenGLDescriptorSet(const DescriptorSetDescriptor & descriptor) : m_textureBindings(descriptor.textures), m_samplerBindings(descriptor.samplers)
{
}

auto OpenGLDescriptorSet::textures() const noexcept -> const std::vector<TextureBinding> &
{
    return m_textureBindings;
}

auto OpenGLDescriptorSet::samplers() const noexcept -> const std::vector<SamplerBinding> &
{
    return m_samplerBindings;
}

} // namespace ProtonEngine::Renderer::OpenGL

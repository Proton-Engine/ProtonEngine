// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/isampler.h"
#include "protonengine/renderer/itexture.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer
{

struct BufferBinding
{
    uint32_t binding;
    IBuffer & buffer;

    // uint64_t offset;
    // uint64_t size;
};

struct TextureBinding
{
    uint32_t binding;
    ITexture & texture;
};

struct SamplerBinding
{
    uint32_t binding;
    ISampler & sampler;
};

struct DescriptorSetDescriptor
{
    std::vector<BufferBinding> buffers;
    std::vector<TextureBinding> textures;
    std::vector<SamplerBinding> samplers;
};

class IDescriptorSet
{
public:
    IDescriptorSet() = default;
    virtual ~IDescriptorSet() = default;
    IDescriptorSet(const IDescriptorSet &) = delete;
    IDescriptorSet & operator=(const IDescriptorSet &) = delete;
    IDescriptorSet(IDescriptorSet &&) = delete;
    IDescriptorSet & operator=(IDescriptorSet &&) = delete;
};

} // namespace ProtonEngine::Renderer
/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/ishader.h"

#include <cstdint>
#include <memory>
#include <vector>

namespace ProtonEngine::Renderer
{

enum class VertexFormat
{
    Float2,
    Float3
};

struct VertexAttributeDescriptor
{
    uint32_t location{};
    VertexFormat format{};
    uint32_t offset{};
    uint32_t binding{};
};

struct VertexLayoutDescriptor
{
    uint32_t stride{};
    std::vector<VertexAttributeDescriptor> attributes{};
};

struct PipelineDescriptor
{
    VertexLayoutDescriptor vertexAttributeDescriptor;
    std::unique_ptr<IShader> shader;
};

class IPipeline
{
public:
    IPipeline() = default;
    virtual ~IPipeline() = default;
    IPipeline(const IPipeline &) = delete;
    IPipeline(IPipeline &&) = delete;
    IPipeline & operator=(const IPipeline &) = delete;
    IPipeline & operator=(IPipeline &&) = delete;
};

} // namespace ProtonEngine::Renderer
// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/itexture.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer
{

enum class ScalingMode
{
    LINEAR,
    NEAREST
};

enum class WrappingMode
{
    REPEAT,
    CLAMP_TO_EDGE
};

struct SamplerDescriptor
{
    ScalingMode scalingMode;
    WrappingMode wrappingMode;
};

class ISampler
{
public:
    ISampler() = default;
    virtual ~ISampler() = default;
    ISampler(const ISampler &) = delete;
    ISampler & operator=(const ISampler &) = delete;
    ISampler(ISampler &&) = delete;
    ISampler & operator=(ISampler &&) = delete;
};

} // namespace ProtonEngine::Renderer
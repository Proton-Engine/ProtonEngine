// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/vertex.h"

#include <vector>

namespace ProtonEngine::Renderer
{

class IRendererInternal
{
public:
    virtual ~IRendererInternal() = default;

    [[nodiscard]] virtual auto createBuffer(const std::vector<Vertex> & vertices,
                                            const std::vector<uint32_t> & indices) const noexcept -> std::unique_ptr<IBuffer> = 0;
};

} // namespace ProtonEngine::Renderer

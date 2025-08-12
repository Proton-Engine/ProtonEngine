// Copyright © 2025. Proton Engine
// Licensed using the MIT license

#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace ProtonEngine::Renderer
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    [[nodiscard]] bool operator==(const Vertex & other) const noexcept = default;
};

} // namespace ProtonEngine::Renderer
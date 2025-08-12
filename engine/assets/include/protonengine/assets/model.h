/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/export.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <vector>

namespace ProtonEngine::Assets
{

struct Face
{
    std::array<int32_t, 3> vertexIndex;
    std::array<int32_t, 3> normalIndex;
    std::array<int32_t, 3> textureIndex;
};

class PROTONENGINE_ASSETS_EXPORT Model
{
public:
    Model(std::vector<Face> && indices, std::vector<glm::vec3> && vertices,
          std::vector<glm::vec3> && normals, std::vector<glm::vec2> && textureCoordinates);

    [[nodiscard]] const std::vector<Face> & getFaces() const noexcept;
    [[nodiscard]] const std::vector<glm::vec3> & getVertices() const noexcept;
    [[nodiscard]] const std::vector<glm::vec3> & getNormals() const noexcept;
    [[nodiscard]] const std::vector<glm::vec2> & getTextureCoordinates() const noexcept;

private:
    std::vector<Face> m_indices;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_normals;
    std::vector<glm::vec2> m_textureCoordinates;
};

} // namespace ProtonEngine::Assets
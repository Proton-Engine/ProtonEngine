/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/assets/model.h"

namespace ProtonEngine::Assets
{

Model::Model(std::vector<Face> && indices, std::vector<glm::vec3> && vertices,
             std::vector<glm::vec3> && normals, std::vector<glm::vec2> && textureCoordinates) :
    m_indices(indices),
    m_vertices(vertices),
    m_normals(normals),
    m_textureCoordinates(textureCoordinates)
{
}

const std::vector<Face> & Model::getFaces() const noexcept
{
    return m_indices;
}

const std::vector<glm::vec3> & Model::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<glm::vec3> & Model::getNormals() const noexcept
{
    return m_normals;
}

const std::vector<glm::vec2> & Model::getTextureCoordinates() const noexcept
{
    return m_textureCoordinates;
}

} // namespace ProtonEngine::Assets
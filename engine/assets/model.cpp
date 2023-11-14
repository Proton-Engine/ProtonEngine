/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/assets/model.h"

namespace ProtonEngine::Assets
{

Model::Model(std::vector<float> vertices, std::vector<float> normals, std::vector<float> textureCoordinates) :
    m_vertices(std::move(vertices)),
    m_normals(std::move(normals)),
    m_textureCoordinates(std::move(textureCoordinates))
{
}

const std::vector<float> & Model::getVertices() const noexcept
{
    return m_vertices;
}

const std::vector<float> & Model::getNormals() const noexcept
{
    return m_normals;
}

const std::vector<float> & Model::getTextureCoordinates() const noexcept
{
    return m_textureCoordinates;
}

} // namespace ProtonEngine::Assets
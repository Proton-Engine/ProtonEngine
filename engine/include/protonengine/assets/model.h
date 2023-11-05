/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <vector>

namespace ProtonEngine::Assets
{

class PROTON_API Model
{
public:
    Model(std::vector<float> vertices, std::vector<float> normals, std::vector<float> textureCoordinates);

    [[nodiscard]] const std::vector<float> & getVertices() const noexcept;
    [[nodiscard]] const std::vector<float> & getNormals() const noexcept;
    [[nodiscard]] const std::vector<float> & getTextureCoordinates() const noexcept;
private:
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_textureCoordinates;
};

} // namespace ProtonEngine::Assets
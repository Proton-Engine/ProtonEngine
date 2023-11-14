/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer {

class PROTON_API Mesh
{
public:
    Mesh(const std::vector<float> & meshData, const std::vector<float> & textureCoordinates);
    ~Mesh();

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    [[nodiscard]] int32_t verticesCount() const noexcept;

private:
    uint32_t m_vertexArrayId{};
    uint32_t m_vertexBufferId{};
    uint32_t m_textureBufferId{};
    int32_t m_verticesCount{};
};

}
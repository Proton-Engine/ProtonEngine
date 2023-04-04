/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <cinttypes>
#include <vector>

namespace ProtonEngine::Renderer {

class Mesh
{
public:
    Mesh(const std::vector<float> & meshData, const std::vector<float> & colorData);
    ~Mesh();

    Mesh(Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh operator=(Mesh &) = delete;
    Mesh operator=(Mesh &&) = delete;

    void enableForDrawing() const noexcept;
    void disableForDrawing() const noexcept;
    [[nodiscard]] uint32_t vertices() const noexcept;

private:
    uint32_t m_vertexArrayId{};
    uint32_t m_vertexBufferId{};
    uint32_t m_colorBufferId{};
    uint32_t m_verticesCount{};
};

}
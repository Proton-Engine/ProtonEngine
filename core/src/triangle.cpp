/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include "protonengine/core/triangle.h"

#include <vector>

namespace ProtonEngine::Core
{

static std::vector<float> triangleVerticesData
    {
        -1.f, -1.f, 0.0f,
        0.f, 1.f, 0.f,
        1.f, -1.f, 0.f
    };

static std::vector<float> triangleColorData
    {
        -1.f, -1.f, 0.0f,
        0.f, 1.f, 0.f,
        1.f, -1.f, 0.f
    };

Triangle::Triangle() :
    Renderer::Mesh(triangleVerticesData, triangleColorData)
{
}

}

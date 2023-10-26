/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include "protonengine/core/triangle.h"

#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>

namespace ProtonEngine::Core
{

static std::vector<float> triangleVerticesData
    {
        -1.f, -1.f, 0.0f,
        0.f, 1.f, 0.f,
        1.f, -1.f, 0.f
    };

static std::vector<float> generateRandomFloatVector()
{
    std::vector<float> result;

    std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    for(size_t i = 0; i < 6; i++)
    {
        const auto number = std::rand();
        result.push_back(number % 255 / 255.f);
    }

    return result;
}

Triangle::Triangle() :
    Renderer::Mesh(triangleVerticesData, generateRandomFloatVector())
{
}

}

/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/cube.h"

#include <vector>

static const std::vector<float> cubeVertexBufferData = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static const std::vector<float> cubeTextureCoordinates = {
    -1.0f,-1.0f,
    -1.0f,-1.0f,
    -1.0f, 1.0f,
    1.0f, 1.0f,
    -1.0f,-1.0f,
    -1.0f, 1.0f,
    1.0f,-1.0f,
    -1.0f,-1.0f,
    1.0f,-1.0f,
    1.0f, 1.0f,
    1.0f,-1.0f,
    -1.0f,-1.0f,
    -1.0f,-1.0f,
    -1.0f, 1.0f,
    -1.0f, 1.0f,
    1.0f,-1.0f,
    -1.0f,-1.0f,
    -1.0f,-1.0f,
    -1.0f, 1.0f,
    -1.0f,-1.0f,
    1.0f,-1.0f,
    1.0f, 1.0f,
    1.0f,-1.0f,
    1.0f, 1.0f,
    1.0f,-1.0f,
    1.0f, 1.0f,
    1.0f,-1.0f,
    1.0f, 1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
    -1.0f, 1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
    1.0f,-1.0f
};

Cube::Cube() :
    ProtonEngine::Renderer::Mesh(cubeVertexBufferData, cubeTextureCoordinates)
{
}

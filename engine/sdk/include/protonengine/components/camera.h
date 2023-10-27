/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "protonengine/renderer/mesh.h"

#include <glm/vec3.hpp>

#include <string>
#include <memory>

namespace ProtonEngine::Components
{

struct Camera
{
    enum class Projection
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    Projection projection;
    float clippingPlaneNear;
    float clippingPlaneFar;
    float fieldOfView;
    bool isMainCamera;
};

} // namespace ProtonEngine::Components
/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/mesh.h"
#include "protonengine/proton_interface.h"

#include <glm/vec3.hpp>

#include <string>
#include <memory>

namespace ProtonEngine::Components
{

struct PROTON_API Camera
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
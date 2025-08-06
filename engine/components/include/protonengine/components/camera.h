/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/components/export.h"

namespace ProtonEngine::Components
{

struct PROTONENGINE_COMPONENTS_EXPORT Camera
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
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"

namespace ProtonEngine::Core::Components
{

struct PROTONENGINE_CORE_EXPORT Camera
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

} // namespace ProtonEngine::Core::Components
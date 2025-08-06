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

    Camera(Projection projection, float clipping_plane_near, float clipping_plane_far, float field_of_view, bool is_main_camera) :
        projection(projection),
        clippingPlaneNear(clipping_plane_near),
        clippingPlaneFar(clipping_plane_far),
        fieldOfView(field_of_view),
        isMainCamera(is_main_camera) {}

    Camera() = default;
};

} // namespace ProtonEngine::Core::Components
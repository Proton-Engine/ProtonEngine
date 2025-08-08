/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/camera.h"

namespace ProtonEngine::Core::Components
{

struct CameraComponent
{
    using Projection = Renderer::Camera::Projection;

    CameraComponent() = default;

    CameraComponent(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView, bool isMainCamera) :
        camera(projection, clippingPlaneNear, clippingPlaneFar, fieldOfView, isMainCamera)
    {
    }

    Renderer::Camera camera;
};

} // namespace ProtonEngine::Core::Components
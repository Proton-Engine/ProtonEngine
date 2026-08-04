/*
 * Copyright © 2022-2026. Proton Engine
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

    CameraComponent(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView)
        : camera(projection, clippingPlaneNear, clippingPlaneFar, fieldOfView)
    {
    }

    CameraComponent(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView, std::unique_ptr<Renderer::IFrameBuffer> && renderBuffer)
        : camera(projection, clippingPlaneNear, clippingPlaneFar, fieldOfView, std::move(renderBuffer))
    {
    }

    Renderer::Camera camera;
};

} // namespace ProtonEngine::Core::Components
/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

namespace ProtonEngine::Renderer
{

struct Camera
{
    enum class Projection
    {
        ORTHOGRAPHIC,
        PERSPECTIVE
    };

    Camera() = default;

    Camera(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView, bool isMainCamera)
        : projection(projection)
        , clippingPlaneNear(clippingPlaneNear)
        , clippingPlaneFar(clippingPlaneFar)
        , fieldOfView(fieldOfView)
        , isMainCamera(isMainCamera)
    {
    }

    Projection projection = Projection::PERSPECTIVE;
    float clippingPlaneNear = 0.1f;
    float clippingPlaneFar = 100.0f;
    float fieldOfView = 60;
    bool isMainCamera = false;
};

} // namespace ProtonEngine::Renderer

/*
 * Copyright © 2025. Proton Engine
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

    Camera(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView, bool isMainCamera) :
        projection(projection),
        clippingPlaneNear(clippingPlaneNear),
        clippingPlaneFar(clippingPlaneFar),
        fieldOfView(fieldOfView),
        isMainCamera(isMainCamera) {}

    Projection projection;
    float clippingPlaneNear;
    float clippingPlaneFar;
    float fieldOfView;
    bool isMainCamera;
};

} // namespace ProtonEngine::Renderer

/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once
#include "protonengine/renderer/iframe_buffer.h"

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
        , renderBuffer(nullptr)
    {
    }

    [[nodiscard]] auto isMainCamera() const noexcept
    {
        return renderBuffer == nullptr;
    }

    Projection projection = Projection::PERSPECTIVE;
    float clippingPlaneNear = 0.1f;
    float clippingPlaneFar = 100.0f;
    float fieldOfView = 60;
    std::unique_ptr<Renderer::IFrameBuffer> renderBuffer;
};

} // namespace ProtonEngine::Renderer

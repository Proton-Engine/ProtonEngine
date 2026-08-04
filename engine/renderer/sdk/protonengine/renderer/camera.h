/*
 * Copyright © 2025-2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/clear_mode.h"
#include "protonengine/renderer/iframe_buffer.h"

#include <glm/gtc/constants.hpp>
#include <glm/vec4.hpp>
#include <memory>

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

    Camera(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView)
        : projection(projection)
        , clippingPlaneNear(clippingPlaneNear)
        , clippingPlaneFar(clippingPlaneFar)
        , fieldOfView(fieldOfView)
        , renderBuffer(nullptr)
    {
    }

    Camera(Projection projection, float clippingPlaneNear, float clippingPlaneFar, float fieldOfView, std::unique_ptr<IFrameBuffer> && renderBuffer)
        : projection(projection)
        , clippingPlaneNear(clippingPlaneNear)
        , clippingPlaneFar(clippingPlaneFar)
        , fieldOfView(fieldOfView)
        , renderBuffer(std::move(renderBuffer))
    {
    }

    [[nodiscard]] auto isMainCamera() const noexcept
    {
        return renderBuffer == nullptr;
    }

    glm::vec4 clearColor = glm::vec4{0, 0, 0, 1};
    ClearMode clearMode = Renderer::ClearMode::ColorAndDepth;

    Projection projection = Projection::PERSPECTIVE;
    float clippingPlaneNear = 0.1f;
    float clippingPlaneFar = 100.0f;
    float fieldOfView = 60;
    size_t renderPriority = 0;

    std::unique_ptr<IFrameBuffer> renderBuffer;
};

} // namespace ProtonEngine::Renderer

/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "camera_controller.h"

#include "protonengine/core/components/mesh_renderer.h"

#include <protonengine/core/components/transform_component.h>

CameraController::CameraController(const ProtonEngine::Core::Entity & entity) :
    NativeScript(entity)
{
}

void CameraController::onUpdate(float timestep)
{
    // TODO: Go to try_get, maybe that will prevent segfault?
    auto transform = getComponent<ProtonEngine::Core::Components::TransformComponent>();

    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_A) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.x -= static_cast<float>(5.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_D) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.x += static_cast<float>(5.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_W) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.y += static_cast<float>(5.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_S) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.y -= static_cast<float>(5.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_LEFT_SHIFT) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.z -= static_cast<float>(5.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_LEFT_CONTROL) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position.z += static_cast<float>(5.0f * timestep);
    }
}
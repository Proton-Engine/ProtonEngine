/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "camera_controller.h"

#include <protonengine/core/components/transform.h>

void CameraController::onUpdate(float timestep)
{
    auto * transform = getComponent<ProtonEngine::Core::Components::Transform>();

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_A) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.x -= static_cast<float>(5.0f * timestep);
    }

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_D) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.x += static_cast<float>(5.0f * timestep);
    }

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_W) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.y += static_cast<float>(5.0f * timestep);
    }

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_S) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.y -= static_cast<float>(5.0f * timestep);
    }

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_LEFT_SHIFT) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.z -= static_cast<float>(5.0f * timestep);
    }

    if (getKeyState(ProtonEngine::Core::KeyCode::KEY_LEFT_CONTROL) == ProtonEngine::Core::KeyState::PRESSED)
    {
        transform->position.z += static_cast<float>(5.0f * timestep);
    }
}
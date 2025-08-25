/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "camera_controller.h"

#include "glm/fwd.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"
#include "glm/vec4.hpp"
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
        transform->transform.position -= rotateVector(glm::vec3{5.0f * timestep, 0, 0}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_D) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position += rotateVector(glm::vec3{5.0f * timestep, 0, 0}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_W) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position += rotateVector(glm::vec3{0, 5.0f * timestep, 0}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_S) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position -= rotateVector(glm::vec3{0, 5.0f * timestep, 0}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_LEFT_SHIFT) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position -= rotateVector(glm::vec3{0, 0, 5.0f * timestep}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_LEFT_CONTROL) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.position += rotateVector(glm::vec3{0, 0, 5.0f * timestep}, transform->transform.rotation);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_Q) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.rotation.y += static_cast<float>(180.0f * timestep);
    }
    if (getKeyState(ProtonEngine::Common::KeyCode::KEY_E) == ProtonEngine::Common::KeyState::PRESSED)
    {
        transform->transform.rotation.y -= static_cast<float>(180.0f * timestep);
    }
}

glm::vec3 CameraController::rotateVector(glm::vec3 vector, glm::vec3 rotation) noexcept
{
    auto rotationMatrix = glm::rotate(glm::mat4(1.0f), -glm::radians(rotation.y), glm::vec3(0, 1, 0));
    rotationMatrix = glm::rotate(rotationMatrix, -glm::radians(rotation.x), glm::vec3(1, 0, 0));
    rotationMatrix = glm::rotate(rotationMatrix, -glm::radians(rotation.z), glm::vec3(0, 0, 1));

    return glm::vec3{rotationMatrix * glm::vec4(vector, 1.0f)};
}
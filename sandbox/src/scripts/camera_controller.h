/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <protonengine/core/components/native_script.h>

class CameraController : public ProtonEngine::Core::Components::NativeScript
{
public:
    CameraController(const ProtonEngine::Core::Entity & entity);

protected:
    void onUpdate(float timestep) override;

private:
    [[nodiscard]] static glm::vec3 rotateVector(glm::vec3 vector, glm::vec3 rotation) noexcept;
};
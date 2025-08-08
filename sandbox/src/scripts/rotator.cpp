/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "rotator.h"

#include <protonengine/core/components/transform_component.h>

void Rotator::onUpdate(float timestep)
{
    auto transform = getComponent<ProtonEngine::Core::Components::TransformComponent>();

    transform->transform.rotation.y += 90.0f * timestep;
}

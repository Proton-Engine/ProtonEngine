/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "rotator.h"

#include <protonengine/components/transform.h>

void Rotator::onUpdate(float timestep)
{
    auto * transform = getComponent<ProtonEngine::Components::Transform>();

    transform->rotation.y += 90.0f * timestep;
}

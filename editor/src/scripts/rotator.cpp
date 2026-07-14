/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "rotator.h"

#include <protonengine/core/components/transform_component.h>

Rotator::Rotator(const ProtonEngine::Core::Entity & entity, float speed) :
    NativeScript(entity),
    m_speed(speed)
{
}

void Rotator::onUpdate(float timestep)
{
    auto transform = getComponent<ProtonEngine::Core::Components::TransformComponent>();

    transform->transform.rotation.y += m_speed * timestep;
    transform->transform.rotation.x += m_speed * 2 * timestep;
    transform->transform.rotation.z += m_speed * 3 * timestep;
}

/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/entity.h"

namespace ProtonEngine::Core
{

Entity::Entity(entt::entity handle, Scene & scene) :
    m_handle(handle), m_scene(scene)
{
}

auto Entity::getHandle() const noexcept -> entt::entity
{
    return m_handle;
}

} // namespace ProtonEngine::Core
/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/entity.h"
#include "protonengine/components/proton_script.h"

namespace ProtonEngine::Core
{

Entity::Entity(entt::entity handle, Scene * scene) :
    m_handle(handle), m_scene(scene)
{
}

auto Entity::getHandle() noexcept -> entt::entity
{
    return m_handle;
}

Entity::Entity() :
    m_handle(), m_scene(nullptr)
{
}

void Entity::addScript(std::unique_ptr<Components::ProtonScript> script)
{
    script->setEntity(*this);
    addComponent(std::move(script));
}

} // namespace ProtonEngine::Core
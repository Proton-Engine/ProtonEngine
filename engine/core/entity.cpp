/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/entity.h"
#include "components/native_script.h"

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

Entity::Entity() : m_handle(), m_scene(nullptr)
{

}

void Entity::addScript(std::unique_ptr<Components::ProtonScript> script)
{
    script->setEntity(*this);
    auto scriptComponent = Components::NativeScript{std::move(script)};
    addComponent(std::move(scriptComponent));
}

} // namespace ProtonEngine::Core
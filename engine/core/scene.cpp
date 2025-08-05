/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/scene.h"
#include "protonengine/components/tag.h"
#include "protonengine/components/transform.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/logger.h"

#include <format>

namespace ProtonEngine::Core
{

auto Scene::addEntity(std::string_view name) noexcept -> Entity
{
    PROTON_LOG_DEBUG(std::format("New entity with name {} created", name));

    const auto entity = m_registry.create();
    m_registry.emplace<Components::Tag>(entity, std::string(name));
    m_registry.emplace<Components::Transform>(entity, glm::vec3{0, 0, 0}, glm::vec3{}, glm::vec3{1, 1, 1});
    return Entity(entity, this);
}

auto Scene::addEntity(std::string_view name, Components::Transform transform) noexcept -> Entity
{
    PROTON_LOG_DEBUG(std::format("New entity with name {} created", name));

    const auto entity = m_registry.create();
    m_registry.emplace<Components::Tag>(entity, std::string(name));
    m_registry.emplace<Components::Transform>(entity, transform.position, transform.rotation, transform.scale);
    return Entity(entity, this);
}

auto Scene::getEntityWithName(std::string_view name) -> Entity
{
    const auto view = m_registry.view<Components::Tag>();

    const auto found = std::ranges::find_if(view, [&](const auto & entity) {
        return view.get<Components::Tag>(entity).tag == name;
    });

    return found != view.end() ? Entity{*found, this} :
                                 throw std::runtime_error(std::format("Entity with name {} not found in the registry", name));
}

auto Scene::getEntityRegistry() noexcept -> entt::registry &
{
    return m_registry;
}

} // namespace ProtonEngine::Core

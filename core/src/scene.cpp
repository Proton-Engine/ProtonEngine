/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/scene.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/components.h"

#include <fmt/format.h>

namespace ProtonEngine::Core
{

auto Scene::addEntity(std::string_view name) noexcept -> Entity
{
    const auto entity = m_registry.create();
    m_registry.emplace<TagComponent>(entity, std::string(name));
    m_registry.emplace<TransformComponent>(entity, glm::vec3{0, 0, -5}, glm::vec3{}, glm::vec3{1, 1, 1});
    return ProtonEngine::Core::Entity(entity, this);
}

auto Scene::getEntityWithName(std::string_view name) -> Entity
{
    const auto view = m_registry.view<TagComponent>();

    const auto found = std::ranges::find_if(view, [&](const auto& entity){
        return view.get<TagComponent>(entity).tag == name;
    });

    return found != view.end() ? Entity{*found, this} :
                                 throw std::runtime_error(fmt::format("Entity with name {} not found in the registry", name));
}

auto Scene::getEntityRegistry() noexcept -> entt::registry &
{
   return m_registry;
}

} // namespace ProtonEngine::Core

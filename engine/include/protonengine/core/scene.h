/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"

#include <entt/entt.hpp>

#include <string_view>

namespace ProtonEngine::Core
{

class Entity;

class PROTON_API Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    Scene(Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene operator=(Scene&) = delete;
    Scene operator=(Scene&&) = delete;

    [[nodiscard]] auto addEntity(std::string_view name) noexcept -> Entity;
    [[nodiscard]] auto getEntityWithName(std::string_view) -> Entity;
    [[nodiscard]] auto getEntityRegistry() noexcept -> entt::registry &;

    void addComponentToEntity(entt::entity handle, auto component) noexcept
    {
        m_registry.emplace<decltype(component)>(handle, std::move(component));
    }
private:
    entt::registry m_registry;
};

} // namespace ProtonEngine::Core
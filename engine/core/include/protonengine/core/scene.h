/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/components/transform_component.h"
#include "protonengine/core/export.h"

#include <entt/entt.hpp>

#include <string_view>

namespace ProtonEngine::Core
{

class Entity;

class PROTONENGINE_CORE_EXPORT Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    Scene(Scene &) = delete;
    Scene(Scene &&) = delete;
    Scene operator=(Scene &) = delete;
    Scene operator=(Scene &&) = delete;

    [[nodiscard]] auto addEntity(std::string_view name) noexcept -> Entity;
    [[nodiscard]] auto addEntity(std::string_view name, Components::TransformComponent transform) noexcept -> Entity;
    [[nodiscard]] auto getEntityWithName(std::string_view) -> Entity;
    [[nodiscard]] auto getEntityRegistry() noexcept -> entt::registry &;

private:
    entt::registry m_registry;
};

} // namespace ProtonEngine::Core
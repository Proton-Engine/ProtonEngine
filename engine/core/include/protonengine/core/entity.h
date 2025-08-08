/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/components/script_component.h"
#include "protonengine/core/export.h"
#include "protonengine/core/scene.h"

#include <entt/entity/entity.hpp>

namespace ProtonEngine::Core::Components
{
class NativeScript;
}

namespace ProtonEngine::Core
{

class PROTONENGINE_CORE_EXPORT Entity
{
public:
    explicit Entity(entt::entity handle, Scene & scene);

    [[nodiscard]] auto getHandle() const noexcept -> entt::entity;

    template <typename T>
    auto addComponent(T component) noexcept -> T &
    {
        return m_scene.getEntityRegistry().emplace<decltype(component)>(m_handle, std::move(component));
    }

    template <typename T, typename... Args>
    auto emplaceComponent(Args &&... args) noexcept -> T &
    {
        return m_scene.getEntityRegistry().emplace<T>(m_handle, std::forward<Args>(args)...);
    }

    template <std::derived_from<Components::NativeScript> T, typename... Args>
    void emplaceScript(Args &&... args) noexcept
    {
        m_scene.getEntityRegistry().emplace<Components::ScriptComponent>(m_handle, std::make_unique<T>(*this, std::forward<Args>(args)...));
    }

    template <typename T>
    [[nodiscard]] auto getComponent() const noexcept -> T &
    {
        return m_scene.getEntityRegistry().get<T>(m_handle);
    }

private:
    entt::entity m_handle;
    Scene & m_scene;
};

} // namespace ProtonEngine::Core
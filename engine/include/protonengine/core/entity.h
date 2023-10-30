/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/scene.h"
#include "protonengine/components/proton_script.h"

#include "protonengine/proton_interface.h"

#include <entt/entity/entity.hpp>

#include <functional>
#include <memory>

namespace ProtonEngine::Core
{

class PROTON_API Entity
{
public:
    Entity();
    explicit Entity(entt::entity handle, Scene * scene);

    [[nodiscard]] auto getHandle() noexcept -> entt::entity;

    void addComponent(auto component) noexcept
    {
        m_scene->addComponentToEntity(m_handle, std::move(component));
    }

    template<typename T, typename = std::enable_if_t<std::is_base_of_v<Components::ProtonScript, T>>>
    void addScript() noexcept
    {
        std::unique_ptr<Components::ProtonScript> script = std::make_unique<T>();
        addScript(std::move(script));
    };
private:
    entt::entity m_handle;
    Scene * m_scene;

    void addScript(std::unique_ptr<Components::ProtonScript> script);
};

} // namespace ProtonEngine::Core
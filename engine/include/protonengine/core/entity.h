/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/scene.h"
#include "protonengine/proton_interface.h"

#include <entt/entity/entity.hpp>

#include <functional>

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
        m_scene->addComponentToEntity(m_handle, component);
    }
private:
    entt::entity m_handle;
    Scene * m_scene;
};

} // namespace ProtonEngine::Core
/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "scene.h"

#include <entt/entity/entity.hpp>

#include <functional>

namespace ProtonEngine::Core
{

class Entity
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
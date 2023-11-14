/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"
#include "protonengine/core/entity.h"

#include "protonengine/proton_interface.h"

#include <chrono>

namespace ProtonEngine::Core
{
    class Entity;
}

namespace ProtonEngine::Components
{

class PROTON_API ProtonScript
{
public:
    ProtonScript() = default;
    virtual ~ProtonScript() = default;

    virtual void onUpdate(float timestep);

    void setEntity(Core::Entity entity);

protected:
    static Core::KeyState getKeyState(Core::Key key);

    template<typename T>
    T * getComponent()
    {
        // TODO: Change for custom assert
        assert(m_entity.has_value());
        return m_entity.value().getComponent<T>();
    }

private:
    std::optional<Core::Entity> m_entity = std::nullopt;
};

} // namespace ProtonEngine::Scripting
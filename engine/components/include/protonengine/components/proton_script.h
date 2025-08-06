/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/entity.h"
#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"

#include "protonengine/components/export.h"

#include <chrono>

namespace ProtonEngine::Core
{
class Entity;
}

namespace ProtonEngine::Components
{

class PROTONENGINE_COMPONENTS_EXPORT ProtonScript
{
public:
    ProtonScript() = default;
    virtual ~ProtonScript() = default;

    virtual void onUpdate(float timestep);

    void setEntity(Core::Entity entity);

protected:
    static Core::KeyState getKeyState(Core::Key key);

    template <typename T>
    T * getComponent()
    {
        // TODO: Change for custom assert
        assert(m_entity.has_value());
        return m_entity.value().getComponent<T>();
    }

private:
    std::optional<Core::Entity> m_entity = std::nullopt;
};

} // namespace ProtonEngine::Components
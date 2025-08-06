/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/entity.h"
#include "protonengine/core/export.h"
#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"

namespace ProtonEngine::Core::Components
{

class PROTONENGINE_CORE_EXPORT NativeScript
{
public:
    NativeScript(const Entity & entity);
    virtual ~NativeScript() = default;

    virtual void onUpdate(float timestep);

protected:
    static Core::KeyState getKeyState(Core::Key key);

    template <typename T>
    T * getComponent()
    {
        return &m_entity.getComponent<T>();
    }

private:
    Entity m_entity;
};

} // namespace ProtonEngine::Core::Components
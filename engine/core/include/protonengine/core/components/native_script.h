/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/common/key_codes.h"
#include "protonengine/common/key_state.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/export.h"

namespace ProtonEngine::Core::Components
{

class PROTONENGINE_CORE_EXPORT NativeScript
{
public:
    explicit NativeScript(const Entity & entity);
    virtual ~NativeScript() = default;

    virtual void onUpdate(float timestep);

protected:
    static Common::KeyState getKeyState(Common::Key key);

    template <typename T>
    T * getComponent()
    {
        return &m_entity.getComponent<T>();
    }

private:
    Entity m_entity;
};

} // namespace ProtonEngine::Core::Components
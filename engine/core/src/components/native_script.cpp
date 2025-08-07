/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/components/native_script.h"

#include "protonengine/core/input.h"

namespace ProtonEngine::Core::Components
{


NativeScript::NativeScript(const Entity & entity) :
    m_entity(entity)
{
}

void NativeScript::onUpdate(float /*timestep*/)
{
}

Common::KeyState NativeScript::getKeyState(Common::Key key)
{
    return Core::Input::getKeyState(key);
}

} // namespace ProtonEngine::Core::Components
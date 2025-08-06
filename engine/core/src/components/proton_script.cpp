/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/components/proton_script.h"

#include "protonengine/core/input.h"

namespace ProtonEngine::Core::Components
{


void ProtonScript::onUpdate(float /*timestep*/)
{
}

Core::KeyState ProtonScript::getKeyState(Core::Key key)
{
    return Core::Input::getKeyState(key);
}

void ProtonScript::setEntity(Core::Entity entity)
{
    m_entity = entity;
}

} // namespace ProtonEngine::Core::Components
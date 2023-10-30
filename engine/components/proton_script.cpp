/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/components/proton_script.h"

#include "core/input.h"

namespace ProtonEngine::Components
{


void ProtonScript::onUpdate()
{

}

Core::KeyState ProtonScript::getKeyState(Core::Key key)
{
    return Core::Input::getKeyState(key);
}

} // namespace ProtonEngine::Components
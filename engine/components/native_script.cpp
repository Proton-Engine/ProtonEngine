/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "native_script.h"

namespace ProtonEngine::Components
{

NativeScript::NativeScript(std::unique_ptr<ProtonScript> script) : m_script(std::move(script))
{

}

void NativeScript::onUpdate(double timestep)
{
    m_script->onUpdate(timestep);
}

} // namespace ProtonEngine::Components
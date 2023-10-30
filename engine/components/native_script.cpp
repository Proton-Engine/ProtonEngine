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

void NativeScript::onUpdate()
{
    m_script->onUpdate();
}

} // namespace ProtonEngine::Components
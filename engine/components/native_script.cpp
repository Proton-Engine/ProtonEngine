/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "native_script.h"

namespace ProtonEngine::Components
{

NativeScript::NativeScript(std::unique_ptr<ProtonScript> script) :
    m_script(std::move(script))
{
}

void NativeScript::onUpdate(float timestep) const
{
    m_script->onUpdate(timestep);
}

} // namespace ProtonEngine::Components
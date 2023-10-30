/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"
#include "protonengine/proton_interface.h"

namespace ProtonEngine::Components
{

class PROTON_API ProtonScript
{
public:
    ProtonScript() = default;
    virtual ~ProtonScript() = default;

    virtual void onUpdate();

protected:
    static Core::KeyState getKeyState(Core::Key key);
};

} // namespace ProtonEngine::Scripting
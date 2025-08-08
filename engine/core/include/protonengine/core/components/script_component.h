/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <memory>

namespace ProtonEngine::Core::Components
{

class NativeScript;

struct ScriptComponent
{
    std::unique_ptr<NativeScript> nativeScript;

    template <std::derived_from<NativeScript> T, typename... Args>
    explicit ScriptComponent(std::unique_ptr<T> && script) :
        nativeScript(std::forward<std::unique_ptr<T>>(script))
    {
    }
};

} // namespace ProtonEngine::Core::Components
/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "protonengine/components/proton_script.h"

#include <memory>

namespace ProtonEngine::Components
{

class NativeScript
{
public:
    explicit NativeScript(std::unique_ptr<ProtonScript> script);
    ~NativeScript() = default;
    NativeScript(const NativeScript&) = delete;
    NativeScript(NativeScript&&) = default;

    NativeScript& operator=(const NativeScript&) = delete;
    NativeScript& operator=(NativeScript&&) = default;


    void onUpdate();

private:
    std::unique_ptr<ProtonScript> m_script;
};

} // namespace ProtonEngine::Components
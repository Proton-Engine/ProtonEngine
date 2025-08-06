/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <protonengine/core/components/native_script.h>

class Rotator : public ProtonEngine::Core::Components::NativeScript
{
protected:
    void onUpdate(float timestep) override;
};
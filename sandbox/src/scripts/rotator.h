/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <protonengine/components/proton_script.h>

class Rotator : public ProtonEngine::Components::ProtonScript
{
protected:
    void onUpdate(float timestep) override;
};
/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include <protonengine/components/proton_script.h>

class CameraController : public ProtonEngine::Components::ProtonScript
{
protected:
    void onUpdate(float timestep) override;
};
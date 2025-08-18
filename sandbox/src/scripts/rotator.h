/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <protonengine/core/components/native_script.h>

class Rotator final : public ProtonEngine::Core::Components::NativeScript
{
public:
    explicit Rotator(const ProtonEngine::Core::Entity & entity, float speed);

protected:
    void onUpdate(float timestep) override;

private:
    float m_speed;
};
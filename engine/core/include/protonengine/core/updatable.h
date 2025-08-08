/*
 * Copyright © 2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

namespace ProtonEngine::Core
{

class Updatable
{
public:
    Updatable() = default;
    virtual ~Updatable() = default;
    Updatable(const Updatable &) = delete;
    Updatable & operator=(const Updatable &) = delete;
    Updatable(Updatable &&) = delete;
    Updatable & operator=(Updatable &&) = delete;

    virtual void onUpdate(float timestep) = 0;
};

} // namespace ProtonEngine::Core
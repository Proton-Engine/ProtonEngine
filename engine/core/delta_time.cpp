/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "delta_time.h"

namespace ProtonEngine::Core
{

std::chrono::time_point<std::chrono::high_resolution_clock> DeltaTime::m_last = std::chrono::high_resolution_clock::now();
std::chrono::milliseconds DeltaTime::m_elapsedMilliseconds;
std::chrono::microseconds DeltaTime::m_elapsedMicroseconds;

void DeltaTime::update() noexcept
{
    const auto currentTime = std::chrono::high_resolution_clock::now();
    const auto elapsed = currentTime - m_last;

    m_elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    m_elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);

    m_last = currentTime;
}

auto DeltaTime::getDeltaTime() noexcept -> std::chrono::milliseconds
{
    return m_elapsedMilliseconds;
}

auto DeltaTime::getDeltaTimeMicroSeconds() noexcept -> std::chrono::microseconds
{
    return m_elapsedMicroseconds;
}

} // namespace ProtonEngine::Core

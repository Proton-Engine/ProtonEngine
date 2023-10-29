/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include <chrono>

namespace ProtonEngine::Core
{

class DeltaTime
{
public:
    DeltaTime() = delete;

    static void update() noexcept;
    [[nodiscard]] static auto getDeltaTime() noexcept -> std::chrono::milliseconds;
    [[nodiscard]] static auto getDeltaTimeMicroSeconds() noexcept -> std::chrono::microseconds;

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> m_last;
    static std::chrono::milliseconds m_elapsedMilliseconds;
    static std::chrono::microseconds m_elapsedMicroseconds;
};

} // namespace ProtonEngine::Core
/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "event_bus.h"
#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"

#include <GLFW/glfw3.h>

#include <array>

namespace ProtonEngine::Core
{

class Input
{
public:
    Input() = delete;

    static void connectToEventBus();

    static void onKeyBoardEvent(Event event, KeyEventEventContext eventContext) noexcept;
    static void onMouseMoveEvent(Event event, MouseMoveEventContext eventContext) noexcept;
    static void onWindowResize(Event event, WindowResizeEventContext eventContext) noexcept;

    [[nodiscard]] static KeyState getKeyState(Key key) noexcept;

private:
    static std::array<KeyState, GLFW_KEY_LAST> m_keyStates;
};

} // namespace ProtonEngine::Core
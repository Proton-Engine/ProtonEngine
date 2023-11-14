/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "input.h"
#include "event_bus.h"

#include <fmt/core.h>

namespace ProtonEngine::Core {

std::array<KeyState, GLFW_KEY_LAST> Input::m_keyStates;

void Input::connectToEventBus()
{
    EventBus::subscribeToEvent(Event::KEY_EVENT, std::function(onKeyBoardEvent));
    EventBus::subscribeToEvent(Event::MOUSE_MOVE_EVENT, std::function(onMouseMoveEvent));
    EventBus::subscribeToEvent(Event::WINDOW_RESIZE_EVENT, std::function(onWindowResize));
}

void Input::onKeyBoardEvent(Event /*event*/, KeyEventEventContext eventContext) noexcept
{
    m_keyStates[eventContext.key] = eventContext.state;
}

void Input::onMouseMoveEvent(Event /*event*/, MouseMoveEventContext eventContext) noexcept
{
    fmt::print("Mouse position: {}, {}\n", eventContext.positionX, eventContext.positionY);
}

void Input::onWindowResize(Event /*event*/, WindowResizeEventContext eventContext) noexcept
{
    fmt::print("Window size: {}, {}\n", eventContext.width, eventContext.height);
}

KeyState Input::getKeyState(Key key) noexcept
{
    return m_keyStates[key];
}

} // namespace ProtonEngine::Core
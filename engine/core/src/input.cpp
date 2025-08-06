/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/input.h"

#include "protonengine/core/event_bus.h"
#include "protonengine/core/logger.h"

#include <GLFW/glfw3.h>

namespace ProtonEngine::Core
{

std::array<KeyState, GLFW_KEY_LAST> Input::m_keyStates;

void Input::connectToEventBus()
{
    PROTON_LOG_INFO("Connecting Input to the event bus");
    EventBus::subscribeToEvent(Event::KEY_EVENT, std::function(onKeyBoardEvent));
    EventBus::subscribeToEvent(Event::MOUSE_MOVE_EVENT, std::function(onMouseMoveEvent));
    EventBus::subscribeToEvent(Event::WINDOW_RESIZE_EVENT, std::function(onWindowResize));
}

void Input::onKeyBoardEvent(Event /*event*/, KeyEventEventContext eventContext) noexcept
{
    m_keyStates[eventContext.key] = eventContext.state;
}

void Input::onMouseMoveEvent(Event /*event*/, MouseMoveEventContext /*eventContext*/) noexcept
{
}

void Input::onWindowResize(Event /*event*/, WindowResizeEventContext /*eventContext*/) noexcept
{
}

KeyState Input::getKeyState(Key key) noexcept
{
    return m_keyStates[key];
}

} // namespace ProtonEngine::Core
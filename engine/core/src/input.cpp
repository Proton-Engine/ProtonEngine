/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/core/input.h"

#include "protonengine/common/event_bus.h"
#include "protonengine/common/logger.h"

#include <GLFW/glfw3.h>

namespace ProtonEngine::Core
{

std::array<Common::KeyState, GLFW_KEY_LAST> Input::m_keyStates;

void Input::connectToEventBus()
{
    PROTON_LOG_INFO("Connecting Input to the event bus");
    Common::EventBus::subscribeToEvent(Common::Event::KEY_EVENT, std::function(onKeyBoardEvent));
    Common::EventBus::subscribeToEvent(Common::Event::MOUSE_MOVE_EVENT, std::function(onMouseMoveEvent));
    Common::EventBus::subscribeToEvent(Common::Event::WINDOW_RESIZE_EVENT, std::function(onWindowResize));
}

void Input::onKeyBoardEvent(Common::Event /*event*/, Common::KeyEventEventContext eventContext) noexcept
{
    m_keyStates[eventContext.key] = eventContext.state;
}

void Input::onMouseMoveEvent(Common::Event /*event*/, Common::MouseMoveEventContext /*eventContext*/) noexcept
{
}

void Input::onWindowResize(Common::Event /*event*/, Common::WindowResizeEventContext /*eventContext*/) noexcept
{
}

Common::KeyState Input::getKeyState(Common::Key key) noexcept
{
    return m_keyStates[key];
}

} // namespace ProtonEngine::Core
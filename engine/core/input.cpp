/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "input.h"

#include <fmt/core.h>

namespace ProtonEngine::Core
{

std::array<KeyState, GLFW_KEY_LAST> Input::m_keyStates;

void Input::onKeyBoardEvent(GLFWwindow * /*window*/, int key, int /*scancode*/, int action, int /*mods*/) noexcept
{
    if (action == GLFW_PRESS)
        m_keyStates[key] = KeyState::PRESSED;
    else if (action == GLFW_RELEASE)
        m_keyStates[key] = KeyState::RELEASED;
}

KeyState Input::getKeyState(Key key) noexcept
{
    return m_keyStates[key];
}

} // namespace ProtonEngine::Core
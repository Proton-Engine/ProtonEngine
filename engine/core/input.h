/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

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

    static void onKeyBoardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) noexcept;

    [[nodiscard]] static KeyState getKeyState(Key key) noexcept;

private:
    static std::array<KeyState, GLFW_KEY_LAST> m_keyStates;
};

} // namespace ProtonEngine::Core
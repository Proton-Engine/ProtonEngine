/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/export.h"

#include "protonengine/common/event_bus.h"
#include "protonengine/common/key_codes.h"
#include "protonengine/common/key_state.h"

// TODO: Remove GLFW here
#include <GLFW/glfw3.h>

#include <array>

namespace ProtonEngine::Core
{

class PROTONENGINE_EXPORT Input
{
public:
    Input() = delete;

    static void connectToEventBus();

    static void onKeyBoardEvent(Common::Event event, Common::KeyEventEventContext eventContext) noexcept;
    static void onMouseMoveEvent(Common::Event event, Common::MouseMoveEventContext eventContext) noexcept;
    static void onWindowResize(Common::Event event, Common::WindowResizeEventContext eventContext) noexcept;

    [[nodiscard]] static Common::KeyState getKeyState(Common::Key key) noexcept;
};

} // namespace ProtonEngine::Core
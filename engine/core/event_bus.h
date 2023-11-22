/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/key_codes.h"
#include "protonengine/core/key_state.h"

#include <map>
#include <vector>
#include <functional>
#include <variant>

namespace ProtonEngine::Core
{

enum class Event
{
    KEY_EVENT,
    MOUSE_MOVE_EVENT,

    WINDOW_RESIZE_EVENT
};

struct KeyEventEventContext
{
    Key key;
    KeyState state;
};

struct MouseMoveEventContext
{
    double positionX;
    double positionY;
};

struct WindowResizeEventContext
{
    int width;
    int height;
};

using EventContext = std::variant<KeyEventEventContext, MouseMoveEventContext, WindowResizeEventContext>;

class EventBus
{
public:
    template<typename T>
    static void subscribeToEvent(Event event, std::function<void(Event, T)> callback)
    {
        subscribeToEventGeneric(event, [callback](Event event, EventContext eventContext)
                         {
                             callback(event, std::get<T>(eventContext));
                         });
    }

    static void fireEvent(Event event, EventContext context);
private:
    static std::map<Event, std::vector<std::function<void(Event, EventContext)>>> m_eventListeners;

    static void subscribeToEventGeneric(Event event, std::function<void(Event, EventContext)> callback);

};

} // namespace ProtonEngine::Core
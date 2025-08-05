/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "event_bus.h"

#include "protonengine/core/logger.h"

#include <format>

namespace ProtonEngine::Core
{

std::map<Event, std::vector<std::function<void(Event, EventContext)>>> EventBus::m_eventListeners{};

static constexpr std::string parseEventToString(Event event)
{
    switch (event)
    {
    case Event::KEY_EVENT:
        return "KEY_EVENT";
    case Event::MOUSE_MOVE_EVENT:
        return "MOUSE_MOVE_EVENT";
    case Event::WINDOW_RESIZE_EVENT:
        return "WINDOW_RESIZE_EVENT";
    }

    return "UNKNOWN_EVENT";
}

void EventBus::fireEvent(Event event, EventContext context)
{
    PROTON_LOG_TRACE(std::format("Event {} fired", parseEventToString(event)));

    if (!m_eventListeners.contains(event))
    {
        return;
    }

    for (const auto & function : m_eventListeners[event])
    {
        function(event, context);
    }
}

void EventBus::subscribeToEventGeneric(Event event, std::function<void(Event, EventContext)> callback)
{
    PROTON_LOG_DEBUG(std::format("New listener for event {}", parseEventToString(event)));

    if (!m_eventListeners.contains(event))
    {
        m_eventListeners[event] = std::vector<std::function<void(Event, EventContext)>>{};
    }

    m_eventListeners[event].emplace_back(callback);
}

} // namespace ProtonEngine::Core
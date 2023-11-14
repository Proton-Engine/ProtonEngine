/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#include "event_bus.h"

namespace ProtonEngine::Core {

std::map<Event, std::vector<std::function<void(Event, EventContext)>>> EventBus::m_eventListeners{};

void EventBus::fireEvent(Event event, EventContext context)
{
    if (!m_eventListeners.contains(event))
    {
        return;
    }

    for (const auto & function : m_eventListeners[event])
    {
        function(event, context);
    }
}

template <>
void EventBus::subscribeToEvent(Event event, std::function<void(Event, EventContext)> callback)
{
    if (!m_eventListeners.contains(event))
    {
        m_eventListeners[event] = std::vector<std::function<void(Event, EventContext)>>{};
    }

    m_eventListeners[event].emplace_back(callback);
}

} // namespace ProtonEngine::Core
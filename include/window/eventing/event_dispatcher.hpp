#pragma once
#ifndef WINDOW_EVENTING_EVENT_DISPATCHER_HPP_
#define WINDOW_EVENTING_EVENT_DISPATCHER_HPP_

#include "window/eventing/event.hpp"

#include <functional>
#include <cstdint>
#include <unordered_map>

namespace Window::Eventing
{
    using ListenerID = uint64_t;

    class Dispatcher
    {
    public:
        using Callback = std::function<void(IEvent&)>;

        virtual ListenerID operator+=(Callback callback)
        {
            return AddListener(std::move(callback));
        }

        virtual bool operator-=(ListenerID listenerID)
        {
            return RemoveListener(listenerID);
        }

        virtual ListenerID AddListener(Callback callback)
        {
            ListenerID listenerID = m_availableListenerID++;
            m_callbacks.emplace(listenerID, callback);
            return listenerID;
        }

        virtual bool RemoveListener(ListenerID listenerID)
        {
            return m_callbacks.erase(listenerID) != 0;
        }

    protected:
        virtual void removeAllListeners()
        {
            m_callbacks.clear();
        }

        virtual uint64_t getListenerCount()
        {
            return m_callbacks.size();
        }

        virtual void invoke(IEvent& event)
        {
            for (auto const& [key, value] : m_callbacks)
                value(event);
        }

    private:
        std::unordered_map<ListenerID, Callback> m_callbacks;
        ListenerID m_availableListenerID = 0;
    };
}

#endif // WINDOW_EVENTING_EVENT_DISPATCHER_HPP_

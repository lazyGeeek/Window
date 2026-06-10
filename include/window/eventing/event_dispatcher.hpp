#pragma once

#include "window/eventing/event.hpp"

#include <cstdint>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace Window::Eventing
{
    using ListenerID = uint64_t;

    class Dispatcher
    {
    public:
        using Callback = std::function<void(IEvent&)>;

        virtual ~Dispatcher() = default;

        virtual ListenerID AddListener(const Callback& callback)
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            ListenerID listenerID = m_availableListenerID++;
            m_callbacks.emplace(listenerID, callback);
            return listenerID;
        }

        virtual bool RemoveListener(ListenerID listenerID)
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            return m_callbacks.erase(listenerID) != 0;
        }

    protected:
        virtual void RemoveAllListeners()
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            m_callbacks.clear();
        }

        virtual uint64_t GetListenerCount()
        {
            std::lock_guard<std::mutex> lk(m_mutex);
            return m_callbacks.size();
        }

        virtual void Invoke(IEvent& event)
        {
            std::vector<Callback> callbacks;
            {
                std::lock_guard<std::mutex> lk(m_mutex);
                callbacks.reserve(m_callbacks.size());

                for (const auto& cb : m_callbacks)
                    callbacks.push_back(cb.second);
            }

            for (const auto& fc : callbacks)
                fc(event);
        }

    private:
        std::unordered_map<ListenerID, Callback> m_callbacks;
        ListenerID m_availableListenerID = 0;
        std::mutex m_mutex;
    };
} // namespace Window::Eventing

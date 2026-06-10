#pragma once

#include "window/eventing/event_dispatcher.hpp"

namespace Window::Eventing::TestSupport
{
    class TestDispatcher : public Dispatcher
    {
    public:
        void CallInvoke(IEvent& event)
        {
            Invoke(event);
        }

        void CallRemoveAllListeners()
        {
            RemoveAllListeners();
        }

        uint64_t CallGetListenerCount()
        {
            return GetListenerCount();
        }
    };
} // namespace Window::Eventing::TestSupport

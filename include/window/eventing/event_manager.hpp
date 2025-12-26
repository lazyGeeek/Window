#pragma once
#ifndef WINDOW_EVENTING_EVENT_MANAGER_HPP_
#define WINDOW_EVENTING_EVENT_MANAGER_HPP_

#include "window/eventing/event_dispatcher.hpp"
#include "window/utils/non_copyable.hpp"

struct GLFWwindow;

namespace Window::Eventing
{
    class EventManager : public Utils::NonCopyable, public Eventing::Dispatcher
    {
    public:
        EventManager(GLFWwindow* window);
        ~EventManager() override;
    };
}

#endif // WINDOW_EVENTING_EVENT_MANAGER_HPP_

#pragma once
#ifndef WINDOW_EVENTING_EVENT_HPP_
#define WINDOW_EVENTING_EVENT_HPP_

#include <string>

namespace Window::Eventing
{
    enum class EEventType
    {
        None = 0,
        
        WindowClose,
        WindowResize,
        WindowMove,
        WindowMinimize,
        WindowMaximize,
        WindowRestore,
        WindowLostFocus,
        WindowGainFocus,
        FramebufferResize,
        
        KeyPress,
        KeyRelease,
        
        MouseButtonPress,
        MouseButtonRelease,
        MouseMove,
        MouseScroll,
    };

    class IEvent
    {
    public:
        virtual ~IEvent() { };
        
        virtual EEventType GetEventType() const = 0;
        virtual std::string ToString()    const = 0;
    };
}

#endif // WINDOW_EVENTING_EVENT_HPP_

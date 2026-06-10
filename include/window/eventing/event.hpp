#pragma once

#include <string>

namespace Window::Eventing
{
    enum class EEventType : std::uint8_t
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

        EventEnumEnd
    };

    class IEvent
    {
      public:
        virtual ~IEvent() = default;

        [[nodiscard]] virtual EEventType GetEventType() const = 0;
        [[nodiscard]] virtual std::string ToString() const = 0;
    };
} // namespace Window::Eventing

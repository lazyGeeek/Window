#pragma once

#include "window/eventing/event.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/mouse_button.hpp"
#include "window/utils/types.hpp"

namespace Window::Eventing
{
    class KeyPressEvent : public IEvent
    {
    public:
        KeyPressEvent(Inputs::EKey key) : m_key { key }
        { }

        [[nodiscard]] inline Inputs::EKey GetKey() const
        {
            return m_key;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::KeyPress;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Key Press Event";
        }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class KeyReleaseEvent : public IEvent
    {
    public:
        KeyReleaseEvent(Inputs::EKey key) : m_key { key }
        { }

        [[nodiscard]] inline Inputs::EKey GetKey() const
        {
            return m_key;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::KeyRelease;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Key Release Event";
        }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class MousePressEvent : public IEvent
    {
    public:
        MousePressEvent(Inputs::EMouseButton key) : m_key { key }
        { }

        [[nodiscard]] inline Inputs::EMouseButton GetKey() const
        {
            return m_key;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::MouseButtonPress;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Mouse Button Press Event";
        }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseReleaseEvent : public IEvent
    {
    public:
        MouseReleaseEvent(Inputs::EMouseButton key) : m_key { key }
        { }

        [[nodiscard]] inline Inputs::EMouseButton GetKey() const
        {
            return m_key;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::MouseButtonRelease;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Mouse Button Release Event";
        }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseMoveEvent : public IEvent
    {
    public:
        MouseMoveEvent(Utils::PositionDouble pos) : m_pos { pos }
        { }

        [[nodiscard]] inline Utils::PositionDouble GetPosition() const
        {
            return m_pos;
        }

        [[nodiscard]] inline double GetPosX() const
        {
            return m_pos.X;
        }

        [[nodiscard]] inline double GetPosY() const
        {
            return m_pos.Y;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::MouseMove;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Mouse Move Event";
        }

    private:
        Utils::PositionDouble m_pos { .X = 0.0, .Y = 0.0 };
    };

    class MouseScrollEvent : public IEvent
    {
    public:
        MouseScrollEvent(Utils::OffsetDouble offset) : m_offset { offset }
        { }

        [[nodiscard]] inline Utils::OffsetDouble GetOffset() const
        {
            return m_offset;
        }

        [[nodiscard]] inline double GetOffsetX() const
        {
            return m_offset.X;
        }

        [[nodiscard]] inline double GetOffsetY() const
        {
            return m_offset.Y;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::MouseScroll;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Mouse Scroll Event";
        }

    private:
        Utils::OffsetDouble m_offset { .X = 0.0, .Y = 0.0 };
    };
} // namespace Window::Eventing

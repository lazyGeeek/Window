#pragma once
#ifndef WINDOW_EVENTING_INPUT_EVENTS_HPP_
#define WINDOW_EVENTING_INPUT_EVENTS_HPP_

#include "window/eventing/event.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/mouse_button.hpp"

namespace Window::Eventing
{
    class KeyPressedEvent : public IEvent
    {
    public:
        KeyPressedEvent(Inputs::EKey key) : m_key { key } { }

        inline Inputs::EKey GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::KeyPressed; }
        virtual std::string ToString()    const override { return "Key Pressed Event"; }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class KeyReleasedEvent : public IEvent
    {
    public:
        KeyReleasedEvent(Inputs::EKey key) : m_key { key } { }

        inline Inputs::EKey GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::KeyReleased; }
        virtual std::string ToString()    const override { return "Key Released Event"; }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class MousePressedEvent : public IEvent
    {
    public:
        MousePressedEvent(Inputs::EMouseButton key) : m_key { key } { }

        inline Inputs::EMouseButton GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::MouseButtonPressed; }
        virtual std::string ToString()    const override { return "Mouse Button Pressed Event"; }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseReleasedEvent : public IEvent
    {
    public:
        MouseReleasedEvent(Inputs::EMouseButton key) : m_key { key } { }

        inline Inputs::EMouseButton GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::MouseButtonReleased; }
        virtual std::string ToString()    const override { return "Mouse Button Released Event"; }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseMovedEvent : public IEvent
    {
    public:
        MouseMovedEvent(double posX, double posY) :
            m_posX { posX }, m_posY { posY } { }

        inline std::tuple<double, double> GetPosition() const { return { m_posX, m_posY }; }
        inline double GetPosX() const { return m_posX; }
        inline double GetPosY() const { return m_posY; }

        virtual EEventType GetEventType() const override { return EEventType::MouseMoved; }
        virtual std::string ToString()    const override { return "Mouse Moved Event"; }

    private:
        double m_posX = 0.0;
        double m_posY = 0.0;
    };

    class MouseScrolledEvent : public IEvent
    {
    public:
        MouseScrolledEvent(double offsetX, double offsetY) :
            m_offsetX { offsetX }, m_offsetY { offsetY } { }

        inline std::tuple<double, double> GetOffset() const { return { m_offsetX, m_offsetY }; }
        inline double GetOffsetX() const { return m_offsetX; }
        inline double GetOffsetY() const { return m_offsetY; }

        virtual EEventType GetEventType() const override { return EEventType::MouseScrolled; }
        virtual std::string ToString()    const override { return "Mouse Scrolled Event"; }

    private:
        double m_offsetX = 0.0;
        double m_offsetY = 0.0;
    };
}

#endif // WINDOW_EVENTING_INPUT_EVENTS_HPP_

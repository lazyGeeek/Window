#pragma once
#ifndef WINDOW_EVENTING_INPUT_EVENTS_HPP_
#define WINDOW_EVENTING_INPUT_EVENTS_HPP_

#include "window/eventing/event.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/mouse_button.hpp"

namespace Window::Eventing
{
    class KeyPressEvent : public IEvent
    {
    public:
        KeyPressEvent(Inputs::EKey key) : m_key { key } { }

        inline Inputs::EKey GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::KeyPress; }
        virtual std::string ToString()    const override { return "Key Press Event"; }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class KeyReleaseEvent : public IEvent
    {
    public:
        KeyReleaseEvent(Inputs::EKey key) : m_key { key } { }

        inline Inputs::EKey GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::KeyRelease; }
        virtual std::string ToString()    const override { return "Key Release Event"; }

    private:
        Inputs::EKey m_key = Inputs::EKey::Unknown;
    };

    class MousePressEvent : public IEvent
    {
    public:
        MousePressEvent(Inputs::EMouseButton key) : m_key { key } { }

        inline Inputs::EMouseButton GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::MouseButtonPress; }
        virtual std::string ToString()    const override { return "Mouse Button Press Event"; }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseReleaseEvent : public IEvent
    {
    public:
        MouseReleaseEvent(Inputs::EMouseButton key) : m_key { key } { }

        inline Inputs::EMouseButton GetKey() const { return m_key; }

        virtual EEventType GetEventType() const override { return EEventType::MouseButtonRelease; }
        virtual std::string ToString()    const override { return "Mouse Button Release Event"; }

    private:
        Inputs::EMouseButton m_key = Inputs::EMouseButton::Unknown;
    };

    class MouseMoveEvent : public IEvent
    {
    public:
        MouseMoveEvent(double posX, double posY) :
            m_posX { posX }, m_posY { posY } { }

        inline std::tuple<double, double> GetPosition() const { return { m_posX, m_posY }; }
        inline double GetPosX() const { return m_posX; }
        inline double GetPosY() const { return m_posY; }

        virtual EEventType GetEventType() const override { return EEventType::MouseMove; }
        virtual std::string ToString()    const override { return "Mouse Move Event"; }

    private:
        double m_posX = 0.0;
        double m_posY = 0.0;
    };

    class MouseScrollEvent : public IEvent
    {
    public:
        MouseScrollEvent(double offsetX, double offsetY) :
            m_offsetX { offsetX }, m_offsetY { offsetY } { }

        inline std::tuple<double, double> GetOffset() const { return { m_offsetX, m_offsetY }; }
        inline double GetOffsetX() const { return m_offsetX; }
        inline double GetOffsetY() const { return m_offsetY; }

        virtual EEventType GetEventType() const override { return EEventType::MouseScroll; }
        virtual std::string ToString()    const override { return "Mouse Scroll Event"; }

    private:
        double m_offsetX = 0.0;
        double m_offsetY = 0.0;
    };
}

#endif // WINDOW_EVENTING_INPUT_EVENTS_HPP_

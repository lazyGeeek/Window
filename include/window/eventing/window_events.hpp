#pragma once
#ifndef WINDOW_EVENTING_WINDOW_EVENTS_HPP_
#define WINDOW_EVENTING_WINDOW_EVENTS_HPP_

#include "window/eventing/event.hpp"

#include <tuple>

namespace Window::Eventing
{
    class WindowResizeEvent : public IEvent
    {
    public:
        WindowResizeEvent(int32_t width, int32_t height) :
            m_width { width }, m_height { height } { }

        inline std::tuple<int32_t, int32_t> GetSize() const { return { m_width, m_height }; }

        inline int32_t GetWidth() const { return m_width; }
        inline int32_t GetHeight() const { return m_height; }

        virtual EEventType GetEventType() const override { return EEventType::WindowResize; }
        virtual std::string ToString()    const override { return "Window Resize Event"; }

    private:
        int32_t m_width  = 0;
        int32_t m_height = 0;
    };

    class FramebufferResizeEvent : public IEvent
    {
    public:
        FramebufferResizeEvent(int32_t width, int32_t height) :
            m_width { width }, m_height { height } { }

        inline std::tuple<int32_t, int32_t> GetSize() const { return { m_width, m_height }; }

        inline int32_t GetWidth() const { return m_width; }
        inline int32_t GetHeight() const { return m_height; }

        virtual EEventType GetEventType() const override { return EEventType::FramebufferResize; }
        virtual std::string ToString()    const override { return "Framebuffer Resize Event"; }

    private:
        int32_t m_width  = 0;
        int32_t m_height = 0;
    };

    class WindowMoveEvent : public IEvent
    {
    public:
        WindowMoveEvent(int32_t posX, int32_t posY) :
            m_posX { posX }, m_posY { posY } { }

        inline std::tuple<int32_t, int32_t> GetPosition() const { return { m_posX, m_posY }; }

        inline int32_t GetPosX() const { return m_posX; }
        inline int32_t GetPosY() const { return m_posY; }

        virtual EEventType GetEventType() const override { return EEventType::WindowMove; }
        virtual std::string ToString()    const override { return "Window Move Event"; }

    private:
        int32_t m_posX = 0;
        int32_t m_posY = 0;
    };

    class WindowCloseEvent : public IEvent
    {
    public:
        WindowCloseEvent() { }

        virtual EEventType GetEventType() const override { return EEventType::WindowClose; }
        virtual std::string ToString()    const override { return "Window Close Event"; }
    };

    class WindowMinimizeEvent : public IEvent
    {
    public:
        WindowMinimizeEvent() { }

        virtual EEventType GetEventType() const override { return EEventType::WindowMinimize; }
        virtual std::string ToString()    const override { return "Window Minimize Event"; }
    };

    class WindowMaximizeEvent : public IEvent
    {
    public:
        WindowMaximizeEvent() { }

        virtual EEventType GetEventType() const override { return EEventType::WindowMaximize; }
        virtual std::string ToString()    const override { return "Window Maximize Event"; }
    };

    class WindowGainFocusEvent : public IEvent
    {
    public:
        WindowGainFocusEvent() { }

        virtual EEventType GetEventType() const override { return EEventType::WindowGainFocus; }
        virtual std::string ToString()    const override { return "Window GainFocus Event"; }
    };

    class WindowLostFocusEvent : public IEvent
    {
    public:
        WindowLostFocusEvent() { }

        virtual EEventType GetEventType() const override { return EEventType::WindowLostFocus; }
        virtual std::string ToString()    const override { return "Window Lost Focus Event"; }
    };
}

#endif // WINDOW_EVENTING_WINDOW_EVENTS_HPP_

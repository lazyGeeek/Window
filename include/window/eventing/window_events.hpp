#pragma once

#include "window/eventing/event.hpp"
#include "window/utils/types.hpp"

namespace Window::Eventing
{
    class WindowResizeEvent : public IEvent
    {
    public:
        WindowResizeEvent(Utils::SizeInt32 size) : m_size { size }
        { }

        [[nodiscard]] inline Utils::SizeInt32 GetSize() const
        {
            return m_size;
        }

        [[nodiscard]] inline int32_t GetWidth() const
        {
            return m_size.Width;
        }

        [[nodiscard]] inline int32_t GetHeight() const
        {
            return m_size.Height;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowResize;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Resize Event";
        }

    private:
        Utils::SizeInt32 m_size { .Width = 0, .Height = 0 };
    };

    class FramebufferResizeEvent : public IEvent
    {
    public:
        FramebufferResizeEvent(Utils::SizeInt32 size) : m_size { size }
        { }

        [[nodiscard]] inline Utils::SizeInt32 GetSize() const
        {
            return m_size;
        }

        [[nodiscard]] inline int32_t GetWidth() const
        {
            return m_size.Width;
        }

        [[nodiscard]] inline int32_t GetHeight() const
        {
            return m_size.Height;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::FramebufferResize;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Framebuffer Resize Event";
        }

    private:
        Utils::SizeInt32 m_size { .Width = 0, .Height = 0 };
    };

    class WindowMoveEvent : public IEvent
    {
    public:
        WindowMoveEvent(Utils::PositionInt32 pos) : m_pos { pos }
        { }

        [[nodiscard]] inline Utils::PositionInt32 GetPosition() const
        {
            return m_pos;
        }

        [[nodiscard]] inline int32_t GetPosX() const
        {
            return m_pos.X;
        }

        [[nodiscard]] inline int32_t GetPosY() const
        {
            return m_pos.Y;
        }

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowMove;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Move Event";
        }

    private:
        Utils::PositionInt32 m_pos { .X = 0, .Y = 0 };
    };

    class WindowCloseEvent : public IEvent
    {
    public:
        WindowCloseEvent() = default;

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowClose;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Close Event";
        }
    };

    class WindowMinimizeEvent : public IEvent
    {
    public:
        WindowMinimizeEvent() = default;

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowMinimize;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Minimize Event";
        }
    };

    class WindowMaximizeEvent : public IEvent
    {
    public:
        WindowMaximizeEvent() = default;

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowMaximize;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Maximize Event";
        }
    };

    class WindowGainFocusEvent : public IEvent
    {
    public:
        WindowGainFocusEvent() = default;

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowGainFocus;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window GainFocus Event";
        }
    };

    class WindowLostFocusEvent : public IEvent
    {
    public:
        WindowLostFocusEvent() = default;

        [[nodiscard]] EEventType GetEventType() const override
        {
            return EEventType::WindowLostFocus;
        }

        [[nodiscard]] std::string ToString() const override
        {
            return "Window Lost Focus Event";
        }
    };
} // namespace Window::Eventing

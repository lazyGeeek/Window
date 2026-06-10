#include <gtest/gtest.h>

#include "window/eventing/event.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

namespace Window::Eventing
{
    class CustomEvent : public IEvent
    {
    public:
        EEventType GetEventType() const override
        {
            return EEventType::None;
        }
        std::string ToString() const override
        {
            return "Custom Event";
        }
    };

    TEST(EventTest, CustomEvent)
    {
        CustomEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::None);
        EXPECT_EQ(event.ToString(), "Custom Event");
    }

    TEST(EventTest, WindowResizeEvent)
    {
        Utils::SizeInt32 size { .Width = 640, .Height = 480 };
        WindowResizeEvent event(size);
        EXPECT_EQ(event.GetWidth(), 640);
        EXPECT_EQ(event.GetHeight(), 480);
        EXPECT_EQ(event.GetSize(), size);
        EXPECT_EQ(event.GetEventType(), EEventType::WindowResize);
        EXPECT_EQ(event.ToString(), "Window Resize Event");
    }

    TEST(EventTest, FramebufferResizeEvent)
    {
        Utils::SizeInt32 size { .Width = 800, .Height = 600 };
        FramebufferResizeEvent event(size);
        EXPECT_EQ(event.GetWidth(), 800);
        EXPECT_EQ(event.GetHeight(), 600);
        EXPECT_EQ(event.GetSize(), size);
        EXPECT_EQ(event.GetEventType(), EEventType::FramebufferResize);
        EXPECT_EQ(event.ToString(), "Framebuffer Resize Event");
    }

    TEST(EventTest, WindowMoveEvent)
    {
        Utils::PositionInt32 pos { .X = 10, .Y = 20 };
        WindowMoveEvent event(pos);
        EXPECT_EQ(event.GetPosX(), 10);
        EXPECT_EQ(event.GetPosY(), 20);
        EXPECT_EQ(event.GetPosition(), pos);
        EXPECT_EQ(event.GetEventType(), EEventType::WindowMove);
        EXPECT_EQ(event.ToString(), "Window Move Event");
    }

    TEST(EventTest, WindowCloseEvent)
    {
        WindowCloseEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::WindowClose);
        EXPECT_EQ(event.ToString(), "Window Close Event");
    }

    TEST(EventTest, WindowMinimizeEvent)
    {
        WindowMinimizeEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::WindowMinimize);
        EXPECT_EQ(event.ToString(), "Window Minimize Event");
    }

    TEST(EventTest, WindowMaximizeEvent)
    {
        WindowMaximizeEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::WindowMaximize);
        EXPECT_EQ(event.ToString(), "Window Maximize Event");
    }

    TEST(EventTest, WindowGainFocusEvent)
    {
        WindowGainFocusEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::WindowGainFocus);
        EXPECT_EQ(event.ToString(), "Window GainFocus Event");
    }

    TEST(EventTest, WindowLostFocusEvent)
    {
        WindowLostFocusEvent event;
        EXPECT_EQ(event.GetEventType(), EEventType::WindowLostFocus);
        EXPECT_EQ(event.ToString(), "Window Lost Focus Event");
    }

    TEST(EventTest, KeyPressEvent)
    {
        KeyPressEvent event(Inputs::EKey::A);
        EXPECT_EQ(event.GetKey(), Inputs::EKey::A);
        EXPECT_EQ(event.GetEventType(), EEventType::KeyPress);
        EXPECT_EQ(event.ToString(), "Key Press Event");
    }

    TEST(EventTest, KeyReleaseEvent)
    {
        KeyReleaseEvent event(Inputs::EKey::Escape);
        EXPECT_EQ(event.GetKey(), Inputs::EKey::Escape);
        EXPECT_EQ(event.GetEventType(), EEventType::KeyRelease);
        EXPECT_EQ(event.ToString(), "Key Release Event");
    }

    TEST(EventTest, MousePressEvent)
    {
        MousePressEvent event(Inputs::EMouseButton::Left);
        EXPECT_EQ(event.GetKey(), Inputs::EMouseButton::Left);
        EXPECT_EQ(event.GetEventType(), EEventType::MouseButtonPress);
        EXPECT_EQ(event.ToString(), "Mouse Button Press Event");
    }

    TEST(EventTest, MouseReleaseEvent)
    {
        MouseReleaseEvent event(Inputs::EMouseButton::Right);
        EXPECT_EQ(event.GetKey(), Inputs::EMouseButton::Right);
        EXPECT_EQ(event.GetEventType(), EEventType::MouseButtonRelease);
        EXPECT_EQ(event.ToString(), "Mouse Button Release Event");
    }

    TEST(EventTest, MouseMoveEvent)
    {
        Utils::PositionDouble pos { .X = 1.5, .Y = 2.5 };
        MouseMoveEvent event(pos);
        EXPECT_DOUBLE_EQ(event.GetPosX(), 1.5);
        EXPECT_DOUBLE_EQ(event.GetPosY(), 2.5);
        EXPECT_EQ(event.GetPosition(), pos);
        EXPECT_EQ(event.GetEventType(), EEventType::MouseMove);
        EXPECT_EQ(event.ToString(), "Mouse Move Event");
    }

    TEST(EventTest, MouseScrollEvent)
    {
        Utils::OffsetDouble offset { .X = -1.0, .Y = 3.0 };
        MouseScrollEvent event(offset);
        EXPECT_DOUBLE_EQ(event.GetOffsetX(), -1.0);
        EXPECT_DOUBLE_EQ(event.GetOffsetY(), 3.0);
        EXPECT_EQ(event.GetOffset(), offset);
        EXPECT_EQ(event.GetEventType(), EEventType::MouseScroll);
        EXPECT_EQ(event.ToString(), "Mouse Scroll Event");
    }

    TEST(EventTest, AllEventTypesAreDistinct)
    {
        EXPECT_NE(static_cast<int>(EEventType::WindowClose),
                  static_cast<int>(EEventType::KeyPress));
        EXPECT_NE(static_cast<int>(EEventType::MouseMove),
                  static_cast<int>(EEventType::MouseScroll));
    }
} // namespace Window::Eventing

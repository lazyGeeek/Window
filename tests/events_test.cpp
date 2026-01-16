#include <gtest/gtest.h>

#include "window/eventing/event.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

namespace Window::Eventing
{
    class TestEvent : public IEvent
    {
    public:
        EEventType GetEventType() const { return EEventType::None; }
        std::string ToString() const { return "Test Event"; }
    };

    TEST(EventsTest, TestEvent)
    {
        TestEvent testEvent;
        ASSERT_EQ(testEvent.GetEventType(), EEventType::None);
        ASSERT_EQ(testEvent.ToString(), "Test Event");
    }

    TEST(EventsTest, WindowResizeEventTest)
    {
        int32_t width = 100;
        int32_t height = 100;

        std::tuple<int32_t, int32_t> testOutput(width, height);

        WindowResizeEvent testWindowResizeEvent(width, height);

        ASSERT_EQ(testWindowResizeEvent.GetSize(), testOutput);
        ASSERT_EQ(testWindowResizeEvent.GetWidth(), width);
        ASSERT_EQ(testWindowResizeEvent.GetHeight(), height);
        ASSERT_EQ(testWindowResizeEvent.GetEventType(), EEventType::WindowResize);
        ASSERT_EQ(testWindowResizeEvent.ToString(), "Window Resize Event");
    }

    TEST(EventsTest, FramebufferResizeEventTest)
    {
        int32_t width = 100;
        int32_t height = 100;

        std::tuple<int32_t, int32_t> testOutput(width, height);

        FramebufferResizeEvent testFramebufferResizeEvent(width, height);

        ASSERT_EQ(testFramebufferResizeEvent.GetSize(), testOutput);
        ASSERT_EQ(testFramebufferResizeEvent.GetWidth(), width);
        ASSERT_EQ(testFramebufferResizeEvent.GetHeight(), height);
        ASSERT_EQ(testFramebufferResizeEvent.GetEventType(), EEventType::FramebufferResize);
        ASSERT_EQ(testFramebufferResizeEvent.ToString(), "Framebuffer Resize Event");
    }

    TEST(EventsTest, WindowMoveEventTest)
    {
        int32_t posX = 100;
        int32_t posY = 100;

        std::tuple<int32_t, int32_t> testOutput(posX, posY);

        WindowMoveEvent testWindowMoveEvent(posX, posY);

        ASSERT_EQ(testWindowMoveEvent.GetPosition(), testOutput);
        ASSERT_EQ(testWindowMoveEvent.GetPosX(), posX);
        ASSERT_EQ(testWindowMoveEvent.GetPosY(), posY);
        ASSERT_EQ(testWindowMoveEvent.GetEventType(), EEventType::WindowMove);
        ASSERT_EQ(testWindowMoveEvent.ToString(), "Window Move Event");
    }

    TEST(EventsTest, WindowCloseEventTest)
    {
        WindowCloseEvent testWindowCloseEvent;
        ASSERT_EQ(testWindowCloseEvent.GetEventType(), EEventType::WindowClose);
        ASSERT_EQ(testWindowCloseEvent.ToString(), "Window Close Event");
    }


    TEST(EventsTest, WindowMinimizeEventTest)
    {
        WindowMinimizeEvent testWindowMinimizeEvent;
        ASSERT_EQ(testWindowMinimizeEvent.GetEventType(), EEventType::WindowMinimize);
        ASSERT_EQ(testWindowMinimizeEvent.ToString(), "Window Minimize Event");
    }

    TEST(EventsTest, WindowMaximizeEventTest)
    {
        WindowMaximizeEvent testWindowMaximizeEvent;
        ASSERT_EQ(testWindowMaximizeEvent.GetEventType(), EEventType::WindowMaximize);
        ASSERT_EQ(testWindowMaximizeEvent.ToString(), "Window Maximize Event");
    }

    TEST(EventsTest, WindowGainFocusEventTest)
    {
        WindowGainFocusEvent testWindowGainFocusEvent;
        ASSERT_EQ(testWindowGainFocusEvent.GetEventType(), EEventType::WindowGainFocus);
        ASSERT_EQ(testWindowGainFocusEvent.ToString(), "Window GainFocus Event");
    }

    TEST(EventsTest, WindowLostFocusEventTest)
    {
        WindowLostFocusEvent testWindowLostFocusEvent;
        ASSERT_EQ(testWindowLostFocusEvent.GetEventType(), EEventType::WindowLostFocus);
        ASSERT_EQ(testWindowLostFocusEvent.ToString(), "Window Lost Focus Event");
    }

    TEST(EventsTest, KeyPressEventTest)
    {
        Inputs::EKey testKey = Inputs::EKey::Space;

        KeyPressEvent testKeyPressEvent(testKey);

        ASSERT_EQ(testKeyPressEvent.GetKey(), testKey);
        ASSERT_EQ(testKeyPressEvent.GetEventType(), EEventType::KeyPress);
        ASSERT_EQ(testKeyPressEvent.ToString(), "Key Press Event");
    }

    TEST(EventsTest, KeyReleaseEventTest)
    {
        Inputs::EKey testKey = Inputs::EKey::Space;

        KeyReleaseEvent testKeyReleaseEvent(testKey);

        ASSERT_EQ(testKeyReleaseEvent.GetKey(), testKey);
        ASSERT_EQ(testKeyReleaseEvent.GetEventType(), EEventType::KeyRelease);
        ASSERT_EQ(testKeyReleaseEvent.ToString(), "Key Release Event");
    }

    TEST(EventsTest, MousePressEventTest)
    {
        Inputs::EMouseButton testKey = Inputs::EMouseButton::Left;

        MousePressEvent testMousePressEvent(testKey);

        ASSERT_EQ(testMousePressEvent.GetKey(), testKey);
        ASSERT_EQ(testMousePressEvent.GetEventType(), EEventType::MouseButtonPress);
        ASSERT_EQ(testMousePressEvent.ToString(), "Mouse Button Press Event");
    }

    TEST(EventsTest, MouseReleaseEventTest)
    {
        Inputs::EMouseButton testKey = Inputs::EMouseButton::Left;

        MouseReleaseEvent testMouseReleaseEvent(testKey);

        ASSERT_EQ(testMouseReleaseEvent.GetKey(), testKey);
        ASSERT_EQ(testMouseReleaseEvent.GetEventType(), EEventType::MouseButtonRelease);
        ASSERT_EQ(testMouseReleaseEvent.ToString(), "Mouse Button Release Event");
    }

    TEST(EventsTest, MouseMoveEventTest)
    {
        double posX = 10.0f;
        double posY = 10.0f;

        std::tuple<double, double> testOutput(posX, posY);
        
        MouseMoveEvent testMouseMoveEvent(posX, posY);

        ASSERT_EQ(testMouseMoveEvent.GetPosition(), testOutput);
        ASSERT_EQ(testMouseMoveEvent.GetPosX(), posX);
        ASSERT_EQ(testMouseMoveEvent.GetPosY(), posY);
        ASSERT_EQ(testMouseMoveEvent.GetEventType(), EEventType::MouseMove);
        ASSERT_EQ(testMouseMoveEvent.ToString(), "Mouse Move Event");
    }

    TEST(EventsTest, MouseScrollEventTest)
    {
        double offsetX = 10.0f;
        double offsetY = 10.0f;

        std::tuple<double, double> testOutput(offsetX, offsetY);
        
        MouseScrollEvent testMouseScrollEvent(offsetX, offsetY);

        ASSERT_EQ(testMouseScrollEvent.GetOffset(), testOutput);
        ASSERT_EQ(testMouseScrollEvent.GetOffsetX(), offsetX);
        ASSERT_EQ(testMouseScrollEvent.GetOffsetY(), offsetY);
        ASSERT_EQ(testMouseScrollEvent.GetEventType(), EEventType::MouseScroll);
        ASSERT_EQ(testMouseScrollEvent.ToString(), "Mouse Scroll Event");
    }
}

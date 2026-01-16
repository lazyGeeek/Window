#include <gtest/gtest.h>

#include "window/eventing/event_dispatcher.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

#include <map>
#include <memory>
#include <string>

namespace Window::Eventing
{
    class DispatcherTest : public Dispatcher
    {
    public:
        void CallInvoke(IEvent& event)
        {
            Dispatcher::invoke(event);
        }

        void CallRemoveAllListeners()
        {
            Dispatcher::removeAllListeners();
        }

        uint64_t CallGetListenerCount()
        {
            return Dispatcher::getListenerCount();
        }
    };

    class TestEvent : public IEvent
    {
    public:
        EEventType GetEventType() const { return EEventType::None; };
        std::string ToString()    const { return "Test Event"; };
    };

    std::map<std::string, std::shared_ptr<IEvent>> eventsMap =
    {
        { "TestEvent", std::make_shared<TestEvent>() },
        { "WindowResizeEvent", std::make_shared<WindowResizeEvent>(100, 100) },
        { "FramebufferResizeEvent", std::make_shared<FramebufferResizeEvent>(100, 100) },
        { "WindowMoveEvent", std::make_shared<WindowMoveEvent>(100, 100) },
        { "WindowCloseEvent", std::make_shared<WindowCloseEvent>() },
        { "WindowMinimizeEvent", std::make_shared<WindowMinimizeEvent>() },
        { "WindowMaximizeEvent", std::make_shared<WindowMaximizeEvent>() },
        { "WindowGainFocusEvent", std::make_shared<WindowGainFocusEvent>() },
        { "WindowLostFocusEvent", std::make_shared<WindowLostFocusEvent>() },
        { "KeyPressEvent", std::make_shared<KeyPressEvent>(Inputs::EKey::Space) },
        { "KeyReleaseEvent", std::make_shared<KeyReleaseEvent>(Inputs::EKey::Space) },
        { "MouseButtonPressEvent", std::make_shared<MousePressEvent>(Inputs::EMouseButton::Left) },
        { "MouseButtonReleaseEvent", std::make_shared<MouseReleaseEvent>(Inputs::EMouseButton::Left) },
        { "MouseMoveEvent", std::make_shared<MouseMoveEvent>(10.0, 10.0) },
        { "MouseScrollEvent", std::make_shared<MouseScrollEvent>(10.0, 10.0) },  
    };

    class EventsGenerator : public testing::TestWithParam<std::pair<const std::string, std::shared_ptr<IEvent>>> { };

    INSTANTIATE_TEST_SUITE_P
    (
        EventsTest, EventsGenerator,
        testing::ValuesIn(eventsMap),
        [](const testing::TestParamInfo<EventsGenerator::ParamType>& info)
        {
            return info.param.first;
        }
    );

    TEST_P(EventsGenerator, EventDispatcherTest)
    {
        DispatcherTest dispatcherTest;
        std::shared_ptr<IEvent> testEvent = GetParam().second;

        bool calledOperator = false;

        ListenerID testId1 = dispatcherTest += [&](Window::Eventing::IEvent& event)
        {
            calledOperator = true;
            ASSERT_EQ(event.GetEventType(), testEvent->GetEventType());
            ASSERT_EQ(event.ToString(), testEvent->ToString());   
        };

        ASSERT_EQ(dispatcherTest.CallGetListenerCount(), 1);
        ASSERT_EQ(testId1, 0);

        bool calledFunction = false;
        ListenerID testId2 = dispatcherTest.AddListener([&](Window::Eventing::IEvent& event)
        {
            calledFunction = true;
            ASSERT_EQ(event.GetEventType(), testEvent->GetEventType());
            ASSERT_EQ(event.ToString(), testEvent->ToString());   
        });
        
        ASSERT_EQ(dispatcherTest.CallGetListenerCount(), 2);
        ASSERT_EQ(testId2, 1);

        dispatcherTest.CallInvoke(*GetParam().second);

        ASSERT_TRUE(calledOperator);
        ASSERT_TRUE(calledFunction);

        dispatcherTest -= testId1;
        ASSERT_EQ(dispatcherTest.CallGetListenerCount(), 1);

        dispatcherTest.RemoveListener(testId2);
        ASSERT_EQ(dispatcherTest.CallGetListenerCount(), 0);
        
        dispatcherTest.AddListener([](Window::Eventing::IEvent& event) { });
        dispatcherTest.AddListener([](Window::Eventing::IEvent& event) { });

        dispatcherTest.CallRemoveAllListeners();

        ASSERT_EQ(dispatcherTest.CallGetListenerCount(), 0);
    }
}

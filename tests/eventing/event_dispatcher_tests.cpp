#include <gtest/gtest.h>

#include "test_dispatcher.hpp"

#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Window::Eventing
{
    class DispatcherParamEvent : public IEvent
    {
    public:
        EEventType GetEventType() const override
        {
            return EEventType::None;
        }
        std::string ToString() const override
        {
            return "Param Event";
        }
    };

    using EventParam = std::pair<std::string, std::shared_ptr<IEvent>>;

    std::vector<EventParam> MakeDispatcherEvents()
    {
        Utils::SizeInt32 size { .Width = 100, .Height = 100 };
        Utils::PositionInt32 pos { .X = 100, .Y = 100 };
        Utils::PositionDouble posd { .X = 10.0, .Y = 10.0 };
        Utils::OffsetDouble offset { .X = 10.0, .Y = 10.0 };

        return {
            { "None", std::make_shared<DispatcherParamEvent>() },
            { "WindowResize", std::make_shared<WindowResizeEvent>(size) },
            { "FramebufferResize",
              std::make_shared<FramebufferResizeEvent>(size) },
            { "WindowMove", std::make_shared<WindowMoveEvent>(pos) },
            { "WindowClose", std::make_shared<WindowCloseEvent>() },
            { "WindowMinimize", std::make_shared<WindowMinimizeEvent>() },
            { "WindowMaximize", std::make_shared<WindowMaximizeEvent>() },
            { "WindowGainFocus", std::make_shared<WindowGainFocusEvent>() },
            { "WindowLostFocus", std::make_shared<WindowLostFocusEvent>() },
            { "KeyPress",
              std::make_shared<KeyPressEvent>(Inputs::EKey::Space) },
            { "KeyRelease",
              std::make_shared<KeyReleaseEvent>(Inputs::EKey::Space) },
            { "MousePress",
              std::make_shared<MousePressEvent>(Inputs::EMouseButton::Left) },
            { "MouseRelease",
              std::make_shared<MouseReleaseEvent>(Inputs::EMouseButton::Left) },
            { "MouseMove", std::make_shared<MouseMoveEvent>(posd) },
            { "MouseScroll", std::make_shared<MouseScrollEvent>(offset) },
        };
    }

    class DispatcherEventTest : public testing::TestWithParam<EventParam>
    {
    };

    INSTANTIATE_TEST_SUITE_P(
        AllEvents, DispatcherEventTest,
        testing::ValuesIn(MakeDispatcherEvents()),
        [](const testing::TestParamInfo<DispatcherEventTest::ParamType>& info) {
            return info.param.first;
        });

    TEST_P(DispatcherEventTest, AddRemoveAndInvoke)
    {
        TestSupport::TestDispatcher dispatcher;
        const auto& expected = GetParam().second;

        bool calledAddListener = false;
        ListenerID id1 = dispatcher.AddListener([&](IEvent& event) {
            calledAddListener = true;
            EXPECT_EQ(event.GetEventType(), expected->GetEventType());
        });
        EXPECT_EQ(dispatcher.CallGetListenerCount(), 1u);
        EXPECT_EQ(id1, 0u);

        dispatcher.CallInvoke(*expected);
        EXPECT_TRUE(calledAddListener);

        EXPECT_TRUE(dispatcher.RemoveListener(id1));
        EXPECT_EQ(dispatcher.CallGetListenerCount(), 0u);

        dispatcher.AddListener([](IEvent&) { });
        dispatcher.AddListener([](IEvent&) { });
        EXPECT_EQ(dispatcher.CallGetListenerCount(), 2u);
        dispatcher.CallRemoveAllListeners();
        EXPECT_EQ(dispatcher.CallGetListenerCount(), 0u);
    }

    TEST(EventDispatcherTest, RemoveUnknownListenerReturnsFalse)
    {
        TestSupport::TestDispatcher dispatcher;
        EXPECT_FALSE(dispatcher.RemoveListener(99));
    }
} // namespace Window::Eventing

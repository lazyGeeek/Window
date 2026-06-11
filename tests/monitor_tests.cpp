#include "glfw_fixture.hpp"

#include <gtest/gtest.h>

#include "window/monitor.hpp"

namespace Window
{
    using Test::GlfwFixture;
    TEST_F(GlfwFixture, GetPrimaryMonitorNotNull)
    {
        ASSERT_NE(Monitor::GetPrimaryMonitor(), nullptr);
    }

    TEST_F(GlfwFixture, MonitorFromPosition)
    {
        auto [x, y] = m_window->GetPosition();
        Monitor monitor({ .X = x, .Y = y });
        EXPECT_NE(monitor.GetMonitor(), nullptr);
    }

    TEST_F(GlfwFixture, MonitorFromGLFWHandle)
    {
        Monitor monitor(Monitor::GetPrimaryMonitor());
        EXPECT_NE(monitor.GetMonitor(), nullptr);
        EXPECT_TRUE(monitor.IsPrimary());
        EXPECT_FALSE(monitor.GetName().empty());
    }

    TEST_F(GlfwFixture, MonitorGeometry)
    {
        Monitor monitor(Monitor::GetPrimaryMonitor());

        Utils::SizeInt32 wsize = monitor.GetWorkareaSize();
        Utils::PositionInt32 wpos = monitor.GetWorkareaPosition();
        Utils::SizeInt32 size = monitor.GetSize();
        Utils::PositionInt32 pos = monitor.GetPosition();
        Utils::ScaleFloat scale = monitor.GetContentScale();

        EXPECT_GT(wsize.Width, 0);
        EXPECT_GT(wsize.Height, 0);
        EXPECT_GE(wpos.X, 0);
        EXPECT_GE(wpos.Y, 0);
        EXPECT_GT(size.Width, 0);
        EXPECT_GT(size.Height, 0);
        EXPECT_GT(scale.X, 0.0f);
        EXPECT_GT(scale.Y, 0.0f);
    }

    TEST_F(GlfwFixture, MonitorVideoModes)
    {
        Monitor monitor(Monitor::GetPrimaryMonitor());
        auto modes = monitor.GetVideoModes();
        ASSERT_FALSE(modes.empty());

        VideoMode current = monitor.GetVideoMode();
        EXPECT_GT(current.Size.Width, 0);
        EXPECT_GT(current.Size.Height, 0);
        EXPECT_GT(current.RefreshRate, 0);

        bool foundCurrent = false;
        for (const auto& mode : modes) {
            if (mode.Size == current.Size)
                foundCurrent = true;
        }
        EXPECT_TRUE(foundCurrent);
    }

    TEST_F(GlfwFixture, MonitorGammaRampRoundTrip)
    {
        Monitor monitor(Monitor::GetPrimaryMonitor());
        GammaRamp original = monitor.GetGammaRamp();
        ASSERT_NE(original.Size, 0u);
        ASSERT_NE(original.Red, nullptr);
        ASSERT_NE(original.Green, nullptr);
        ASSERT_NE(original.Blue, nullptr);

        EXPECT_NO_THROW(monitor.SetGammaRamp(original));
        GammaRamp restored = monitor.GetGammaRamp();
        EXPECT_EQ(restored.Size, original.Size);
    }

    TEST_F(GlfwFixture, UpdateMonitorChangesHandle)
    {
        auto [x, y] = m_window->GetPosition();
        Monitor monitor({ .X = 0, .Y = 0 });
        GLFWmonitor* before = monitor.GetMonitor();
        monitor.UpdateMonitor({ .X = x, .Y = y });
        EXPECT_NE(monitor.GetMonitor(), nullptr);
        (void)before;
    }
} // namespace Window

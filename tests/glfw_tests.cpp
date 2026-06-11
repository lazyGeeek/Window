#include "glfw_fixture.hpp"

#include <gtest/gtest.h>

namespace Window
{
    using Test::GlfwFixture;
    TEST(GlfwTest, WindowInitDefaults)
    {
        Utils::SizeInt32 defaultSize { .Width = 1280, .Height = 720 };

        WindowInit init;
        EXPECT_TRUE(init.Title.empty());
        EXPECT_EQ(init.Size, defaultSize);
    }

    TEST_F(GlfwFixture, ConstructsWithCustomInit)
    {
        EXPECT_EQ(m_window->GetTitle(), "WindowTests");

        const Utils::SizeInt32& size = m_window->GetSize();

        EXPECT_GE(size.Width, 1);
        EXPECT_GE(size.Height, 1);
    }

    TEST_F(GlfwFixture, SetAndGetTitle)
    {
        m_window->SetTitle("Renamed");
        EXPECT_EQ(m_window->GetTitle(), "Renamed");
    }

    TEST_F(GlfwFixture, SetSizeAndPosition)
    {
        Utils::SizeInt32 size { .Width = 400, .Height = 300 };
        Utils::PositionInt32 pos { .X = 50, .Y = 60 };

        m_window->SetSize(size);
        m_window->SetPosition(pos);
        m_window->PollEvents();

        Utils::SizeInt32 outSize = m_window->GetSize();
        Utils::PositionInt32 outPos = m_window->GetPosition();

        EXPECT_EQ(outSize, size);
        EXPECT_EQ(outPos, pos);
    }

    TEST_F(GlfwFixture, MinMaxSizeLimits)
    {
        Utils::SizeInt32 minSize { .Width = 200, .Height = 150 };
        Utils::SizeInt32 maxSize { .Width = 800, .Height = 600 };

        m_window->SetMinimumSize(minSize);
        m_window->SetMaximumSize(maxSize);

        Utils::SizeInt32 outMinSize = m_window->GetMinimumSize();
        Utils::SizeInt32 outMaxSize = m_window->GetMaximumSize();

        EXPECT_EQ(minSize, outMinSize);
        EXPECT_EQ(maxSize, outMaxSize);
    }

    TEST_F(GlfwFixture, ShouldCloseFlag)
    {
        EXPECT_FALSE(m_window->ShouldClose());

        m_window->SetShouldClose(true);
        EXPECT_TRUE(m_window->ShouldClose());

        m_window->SetShouldClose(false);
        EXPECT_FALSE(m_window->ShouldClose());
    }

    TEST_F(GlfwFixture, CloseWindowSetsShouldClose)
    {
        m_window->CloseWindow();
        EXPECT_TRUE(m_window->ShouldClose());
    }

    TEST_F(GlfwFixture, WindowAttributes)
    {
        EXPECT_TRUE(m_window->IsVisible());
        EXPECT_TRUE(m_window->IsResizable());
        EXPECT_TRUE(m_window->IsDecorated());
        EXPECT_FALSE(m_window->IsFullscreen());
    }

    TEST_F(GlfwFixture, HideAndShow)
    {
        m_window->Hide();
        m_window->PollEvents();

        EXPECT_TRUE(m_window->IsHidden());
        EXPECT_FALSE(m_window->IsVisible());

        m_window->Show();
        m_window->PollEvents();

        EXPECT_FALSE(m_window->IsHidden());
        EXPECT_TRUE(m_window->IsVisible());
    }

    TEST_F(GlfwFixture, Vsync)
    {
        m_window->SetVsync(true);
        EXPECT_TRUE(m_window->HasVsync());

        m_window->SetVsync(false);
        EXPECT_FALSE(m_window->HasVsync());
    }

    TEST_F(GlfwFixture, FramebufferSize)
    {
        Utils::SizeInt32 size = m_window->GetFramebufferSize();
        EXPECT_GT(size.Width, 0);
        EXPECT_GT(size.Height, 0);
    }

    TEST_F(GlfwFixture, ContextManagement)
    {
#ifndef WINDOW_USE_VULKAN
        EXPECT_NO_THROW(m_window->MakeCurrentContext());
        EXPECT_NO_THROW(m_window->SwapBuffers());
#endif
        EXPECT_NO_THROW(m_window->ClearCurrentContext());
    }

    TEST_F(GlfwFixture, DontCareConstant)
    {
        EXPECT_EQ(GLFW::DONT_CARE, -1);
    }

    TEST_F(GlfwFixture, ListenerReceivesResizeOnSetSize)
    {
        bool received = false;
        m_window->AddListener([&](Eventing::IEvent& event) {
            if (event.GetEventType() == Eventing::EEventType::WindowResize)
                received = true;
        });
        m_window->SetSize({ .Width = 360, .Height = 270 });
        m_window->PollEvents();
        EXPECT_TRUE(received);
    }

    TEST_F(GlfwFixture, RestoreMinimizeMaximizeDoNotThrow)
    {
        EXPECT_NO_THROW(m_window->Minimize());
        m_window->PollEvents();

        EXPECT_NO_THROW(m_window->Restore());
        m_window->PollEvents();

        EXPECT_NO_THROW(m_window->Maximize());
        m_window->PollEvents();

        EXPECT_NO_THROW(m_window->Restore());
        m_window->PollEvents();
    }
} // namespace Window

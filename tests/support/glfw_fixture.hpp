#pragma once

#include "window/glfw.hpp"

#include <gtest/gtest.h>

#include <memory>

namespace Window::Test
{
    inline WindowInit MakeTestWindowInit()
    {
        return WindowInit {
            .Title = "WindowTests",
            .Width = 320,
            .Height = 240,
        };
    }

    class GlfwFixture : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            m_window = std::make_unique<GLFW>(MakeTestWindowInit());
            ASSERT_NE(m_window->GetWindow(), nullptr);
        }

        void TearDown() override
        {
            m_window.reset();
        }

        std::unique_ptr<GLFW> m_window;
    };
} // namespace Window::Test

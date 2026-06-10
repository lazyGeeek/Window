#include "glfw_fixture.hpp"

#include <gtest/gtest.h>

#include "window/cursor/cursor.hpp"

namespace Window::Cursor
{
    class CursorFixture : public Window::Test::GlfwFixture
    {
    protected:
        void SetUp() override
        {
            GlfwFixture::SetUp();
            m_cursor = std::make_unique<Cursor>(*m_window);
        }

        void TearDown() override
        {
            m_cursor.reset();
            GlfwFixture::TearDown();
        }

        std::unique_ptr<Cursor> m_cursor;
    };

    TEST_F(CursorFixture, SetAndGetPosition)
    {
        Utils::PositionDouble pos { .X = 100.0, .Y = 150.0 };
        m_cursor->SetPosition(pos);
        EXPECT_EQ(m_cursor->GetPosition(), pos);
    }

    TEST_F(CursorFixture, AllModes)
    {
        EXPECT_NO_THROW(m_cursor->SetMode(ECursorMode::Normal));
        EXPECT_NO_THROW(m_cursor->SetMode(ECursorMode::Hidden));
        EXPECT_NO_THROW(m_cursor->SetMode(ECursorMode::Disabled));
        EXPECT_NO_THROW(m_cursor->SetMode(ECursorMode::Normal));
    }

    TEST_F(CursorFixture, AllShapes)
    {
        const ECursorShape shapes[] = {
            ECursorShape::Arrow, ECursorShape::IBeam,   ECursorShape::CrossHair,
            ECursorShape::Hand,  ECursorShape::HResize, ECursorShape::VResize,
        };

            for (auto shape : shapes) {
                EXPECT_NO_THROW(m_cursor->SetShape(shape));
            }
    }

    TEST_F(CursorFixture, DestructorReleasesCursors)
    {
        auto temporary = std::make_unique<Cursor>(*m_window);
        temporary.reset();
        SUCCEED();
    }
} // namespace Window::Cursor

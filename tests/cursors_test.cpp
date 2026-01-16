#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include "window/glfw.hpp"
#include "window/cursor/cursor.hpp"

namespace Window::Cursor
{
    class CursorTest : public testing::Test
    {
    protected:
        void SetUp() override
        {
            m_window = std::make_shared<GLFW>();

            m_normalCursor = std::make_shared<Cursor>(m_window->GetWindow());
            m_nullCursor = std::make_shared<Cursor>(nullptr);
        }

        void TearDown() override
        {
            m_nullCursor = nullptr;
            m_normalCursor = nullptr;

            m_window = nullptr;
        }

        std::shared_ptr<GLFW> m_window = nullptr;

        std::shared_ptr<Cursor> m_normalCursor = nullptr;
        std::shared_ptr<Cursor> m_nullCursor = nullptr;
    };

    TEST_F(CursorTest, TestPosition)
    {
        std::tuple<double, double> testPosition(100, 150);
        ASSERT_NO_THROW(m_normalCursor->SetPosition(std::get<0>(testPosition), std::get<1>(testPosition)));
        ASSERT_NO_THROW(m_nullCursor->SetPosition(std::get<0>(testPosition), std::get<1>(testPosition)));

        ASSERT_EQ(m_normalCursor->GetPosition(), testPosition);

        std::tuple<double, double> defaultOutput(0.0, 0.0);
        ASSERT_EQ(m_nullCursor->GetPosition(), defaultOutput);
    }

    TEST_F(CursorTest, TestModes)
    {
        ASSERT_NO_THROW(m_normalCursor->SetMode(ECursorMode::Disabled));
        ASSERT_NO_THROW(m_normalCursor->SetMode(ECursorMode::Hidden));
        ASSERT_NO_THROW(m_normalCursor->SetMode(ECursorMode::Normal));

        ASSERT_NO_THROW(m_nullCursor->SetMode(ECursorMode::Disabled));
        ASSERT_NO_THROW(m_nullCursor->SetMode(ECursorMode::Hidden));
        ASSERT_NO_THROW(m_nullCursor->SetMode(ECursorMode::Normal));
    }

    TEST_F(CursorTest, TestShapes)
    {
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::Arrow));
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::CrossHair));
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::Hand));
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::HResize));
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::IBeam));
        ASSERT_NO_THROW(m_normalCursor->SetShape(ECursorShape::VResize));

        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::Arrow));
        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::CrossHair));
        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::Hand));
        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::HResize));
        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::IBeam));
        ASSERT_NO_THROW(m_nullCursor->SetShape(ECursorShape::VResize));
    }
}

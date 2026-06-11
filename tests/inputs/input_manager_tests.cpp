#include "glfw_fixture.hpp"

#include <gtest/gtest.h>

#include "window/inputs/input_manager.hpp"

namespace Window::Inputs
{
    class InputManagerFixture : public Window::Test::GlfwFixture
    {
    protected:
        void SetUp() override
        {
            GlfwFixture::SetUp();
            m_inputs = std::make_unique<InputManager>(*m_window);
        }

        void TearDown() override
        {
            m_inputs.reset();
            GlfwFixture::TearDown();
        }

        std::unique_ptr<InputManager> m_inputs;
    };

    TEST_F(InputManagerFixture, KeyReleasedByDefault)
    {
        EXPECT_EQ(m_inputs->GetKeyState(EKey::Space), EKeyState::Released);
        EXPECT_FALSE(m_inputs->IsKeyPressed(EKey::Space));
        EXPECT_TRUE(m_inputs->IsKeyReleased(EKey::Space));
    }

    TEST_F(InputManagerFixture, MouseButtonReleasedByDefault)
    {
        EXPECT_EQ(m_inputs->GetMouseButtonState(EMouseButton::Left),
                  EMouseButtonState::Released);
        EXPECT_FALSE(m_inputs->IsMouseButtonPressed(EMouseButton::Left));
        EXPECT_TRUE(m_inputs->IsMouseButtonReleased(EMouseButton::Left));
    }

    TEST_F(InputManagerFixture, MultipleKeysQueried)
    {
        EXPECT_TRUE(m_inputs->IsKeyReleased(EKey::Escape));
        EXPECT_TRUE(m_inputs->IsKeyReleased(EKey::Enter));
        EXPECT_TRUE(m_inputs->IsMouseButtonReleased(EMouseButton::B4));
    }
} // namespace Window::Inputs

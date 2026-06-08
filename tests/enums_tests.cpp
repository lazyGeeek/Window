#include <gtest/gtest.h>

#include "window/cursor/cursor_mode.hpp"
#include "window/cursor/cursor_shape.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/key_state.hpp"
#include "window/inputs/mouse_button.hpp"
#include "window/inputs/mouse_button_state.hpp"

namespace Window
{
    TEST(KeyEnumTest, GLFWKeyValues)
    {
        EXPECT_EQ(static_cast<int>(Inputs::EKey::Space), 32);
        EXPECT_EQ(static_cast<int>(Inputs::EKey::A), 65);
        EXPECT_EQ(static_cast<int>(Inputs::EKey::Escape), 256);
        EXPECT_EQ(static_cast<int>(Inputs::EKey::F1), 290);
        EXPECT_EQ(static_cast<int>(Inputs::EKey::Unknown), -1);
    }

    TEST(MouseButtonEnumTest, AliasesMatchGLFW)
    {
        EXPECT_EQ(static_cast<int>(Inputs::EMouseButton::Left), 0);
        EXPECT_EQ(static_cast<int>(Inputs::EMouseButton::Right), 1);
        EXPECT_EQ(static_cast<int>(Inputs::EMouseButton::Middle), 2);
        EXPECT_EQ(Inputs::EMouseButton::Left, Inputs::EMouseButton::B1);
        EXPECT_EQ(Inputs::EMouseButton::Right, Inputs::EMouseButton::B2);
        EXPECT_EQ(Inputs::EMouseButton::Middle, Inputs::EMouseButton::B3);
    }

    TEST(InputStateEnumTest, Values)
    {
        EXPECT_NE(Inputs::EKeyState::Pressed, Inputs::EKeyState::Released);
        EXPECT_NE(Inputs::EMouseButtonState::Pressed,
                  Inputs::EMouseButtonState::Released);
    }

    TEST(CursorEnumTest, GLFWConstants)
    {
        EXPECT_EQ(static_cast<int>(Cursor::ECursorMode::Normal), 0x00034001);
        EXPECT_EQ(static_cast<int>(Cursor::ECursorMode::Hidden), 0x00034002);
        EXPECT_EQ(static_cast<int>(Cursor::ECursorMode::Disabled), 0x00034003);

        EXPECT_EQ(static_cast<int>(Cursor::ECursorShape::Arrow), 0x00036001);
        EXPECT_EQ(static_cast<int>(Cursor::ECursorShape::VResize), 0x00036006);
    }
} // namespace Window

#pragma once

#include "window/glfw.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/key_state.hpp"
#include "window/inputs/mouse_button.hpp"
#include "window/inputs/mouse_button_state.hpp"
#include "window/utils/non_copyable.hpp"

namespace Window::Inputs
{
    class InputManager : public Utils::NonCopyable
    {
    public:
        InputManager(const GLFW& glfw);

        [[nodiscard]] EKeyState GetKeyState(EKey key) const;
        [[nodiscard]] EMouseButtonState
        GetMouseButtonState(EMouseButton button) const;

        [[nodiscard]] bool IsKeyPressed(EKey key) const;
        [[nodiscard]] bool IsKeyReleased(EKey key) const;
        [[nodiscard]] bool IsMouseButtonPressed(EMouseButton button) const;
        [[nodiscard]] bool IsMouseButtonReleased(EMouseButton button) const;

    private:
        const GLFW& m_glfw;
    };
} // namespace Window::Inputs

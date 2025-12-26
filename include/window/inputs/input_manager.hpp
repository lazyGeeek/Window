#pragma once
#ifndef WINDOW_INPUTS_INPUT_MANAGER_HPP_
#define WINDOW_INPUTS_INPUT_MANAGER_HPP_

#include "window/inputs/key.hpp"
#include "window/inputs/key_state.hpp"
#include "window/inputs/mouse_button.hpp"
#include "window/inputs/mouse_button_state.hpp"
#include "window/utils/non_copyable.hpp"

struct GLFWwindow;

namespace Window::Inputs
{
    class InputManager : public Utils::NonCopyable
    {
    public:
        InputManager(GLFWwindow* window);

        EKeyState GetKeyState(EKey key) const;
        EMouseButtonState GetMouseButtonState(EMouseButton button) const;

        bool IsKeyPressed(EKey key) const;
        bool IsKeyReleased(EKey key) const;
        bool IsMouseButtonPressed(EMouseButton button) const;
        bool IsMouseButtonReleased(EMouseButton button) const;

    private:
        GLFWwindow* m_window = nullptr;
    };
}

#endif // WINDOW_INPUTS_INPUT_MANAGER_HPP_

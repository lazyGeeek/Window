#pragma once
#ifndef WINDOW_INPUTS_INPUT_MANAGER_HPP_
#define WINDOW_INPUTS_INPUT_MANAGER_HPP_

#include "window/cursor/cursor_mode.hpp"
#include "window/cursor/cursor_shape.hpp"
#include "window/inputs/key.hpp"
#include "window/inputs/key_state.hpp"
#include "window/inputs/mouse_button.hpp"
#include "window/inputs/mouse_button_state.hpp"

#include <GLFW/glfw3.h>

#include <unordered_map>

namespace Window { class GLFW; }

namespace Window::Inputs
{
    class InputManager
    {
    public:
        InputManager(Window::GLFW* window);
        ~InputManager();

        InputManager(const InputManager& other)             = delete;
        InputManager(InputManager&& other)                  = delete;
        InputManager& operator=(const InputManager& other)  = delete;
        InputManager& operator=(const InputManager&& other) = delete;

        EKeyState GetKeyState(EKey key) const;
        EMouseButtonState GetMouseButtonState(EMouseButton button) const;

        bool IsKeyPressed(EKey key) const;
        bool IsKeyReleased(EKey key) const;
        bool IsMouseButtonPressed(EMouseButton button) const;
        bool IsMouseButtonReleased(EMouseButton button) const;

        void SetCursorPosition(double x, double y);
        std::tuple<double, double> GetCursorPosition() const;

        void SetCursorMode(Cursor::ECursorMode mode);
        void SetCursorShape(Cursor::ECursorShape cursor);

    private:
        Window::GLFW* m_window = nullptr;

        std::unordered_map<Cursor::ECursorShape, GLFWcursor*> m_cursors;
    };
}

#endif // WINDOW_INPUTS_INPUT_MANAGER_HPP_

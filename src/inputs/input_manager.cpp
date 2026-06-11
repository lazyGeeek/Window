#include "window/inputs/input_manager.hpp"

#include <GLFW/glfw3.h>

namespace Window::Inputs
{
    InputManager::InputManager(const GLFW& glfw) : m_glfw { glfw }
    { }

    EKeyState InputManager::GetKeyState(EKey key) const
    {
        GLFWwindow* window = m_glfw.GetWindow();

        if (window && glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS)
            return EKeyState::Pressed;

        return EKeyState::Released;
    }

    EMouseButtonState
    InputManager::GetMouseButtonState(EMouseButton button) const
    {
        GLFWwindow* window = m_glfw.GetWindow();

        if (window &&
            glfwGetMouseButton(window, static_cast<int>(button)) == GLFW_PRESS)
            return EMouseButtonState::Pressed;

        return EMouseButtonState::Released;
    }

    bool InputManager::IsKeyPressed(EKey key) const
    {
        return GetKeyState(key) == EKeyState::Pressed;
    }

    bool InputManager::IsKeyReleased(EKey key) const
    {
        return GetKeyState(key) == EKeyState::Released;
    }

    bool InputManager::IsMouseButtonPressed(EMouseButton button) const
    {
        return GetMouseButtonState(button) == EMouseButtonState::Pressed;
    }

    bool InputManager::IsMouseButtonReleased(EMouseButton button) const
    {
        return GetMouseButtonState(button) == EMouseButtonState::Released;
    }
} // namespace Window::Inputs

#include "window/inputs/input_manager.hpp"
#include "window/glfw.hpp"

namespace Window::Inputs
{
    InputManager::InputManager(Window::GLFW* window) : m_window{ window }
    {
        m_cursors[Cursor::ECursorShape::Arrow]     = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Arrow));
        m_cursors[Cursor::ECursorShape::IBeam]     = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::IBeam));
        m_cursors[Cursor::ECursorShape::CrossHair] = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::CrossHair));
        m_cursors[Cursor::ECursorShape::Hand]      = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::Hand));
        m_cursors[Cursor::ECursorShape::HResize]   = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::HResize));
        m_cursors[Cursor::ECursorShape::VResize]   = glfwCreateStandardCursor(static_cast<int>(Cursor::ECursorShape::VResize));
    }

    InputManager::~InputManager()
    {
        ClearEvents();

        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Arrow]);
        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::IBeam]);
        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::CrossHair]);
        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::Hand]);
        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::HResize]);
        glfwDestroyCursor(m_cursors[Cursor::ECursorShape::VResize]);
    }

    EKeyState InputManager::GetKeyState(EKey key) const
    {
        if (glfwGetKey(m_window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS)
            return EKeyState::Pressed;

        return EKeyState::Released;
    }

    EMouseButtonState InputManager::GetMouseButtonState(EMouseButton button) const
    {
        if (glfwGetMouseButton(m_window->GetWindow(), static_cast<int>(button)) == GLFW_PRESS)
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

    void InputManager::SetCursorPosition(double x, double y)
    {
        glfwSetCursorPos(m_window->GetWindow(), x, y);
    }

    std::tuple<double, double> InputManager::GetCursorPosition() const
    {
        double x = 0.0;
        double y = 0.0;
        glfwGetCursorPos(m_window->GetWindow(), &x, &y);
        return { x, y };
    }

    void InputManager::SetCursorMode(Cursor::ECursorMode mode)
    {
        glfwSetInputMode(m_window->GetWindow(), GLFW_CURSOR, static_cast<int>(mode));
    }

    void InputManager::SetCursorShape(Cursor::ECursorShape cursorShape)
    {
        glfwSetCursor(m_window->GetWindow(), m_cursors[cursorShape]);
    }

    void InputManager::ClearEvents()
    {
        KeyPressedEvent.RemoveAllListeners();
        KeyReleasedEvent.RemoveAllListeners();
        MouseButtonPressedEvent.RemoveAllListeners();
        MouseButtonReleasedEvent.RemoveAllListeners();
        CursorMoveEvent.RemoveAllListeners();
    }
}

#include "window/cursor/cursor.hpp"

#include <GLFW/glfw3.h>

namespace Window::Cursor
{
    Cursor::Cursor(GLFWwindow* window) : m_window { window }
    {
        m_cursors[ECursorShape::Arrow]     = glfwCreateStandardCursor(static_cast<int>(ECursorShape::Arrow));
        m_cursors[ECursorShape::IBeam]     = glfwCreateStandardCursor(static_cast<int>(ECursorShape::IBeam));
        m_cursors[ECursorShape::CrossHair] = glfwCreateStandardCursor(static_cast<int>(ECursorShape::CrossHair));
        m_cursors[ECursorShape::Hand]      = glfwCreateStandardCursor(static_cast<int>(ECursorShape::Hand));
        m_cursors[ECursorShape::HResize]   = glfwCreateStandardCursor(static_cast<int>(ECursorShape::HResize));
        m_cursors[ECursorShape::VResize]   = glfwCreateStandardCursor(static_cast<int>(ECursorShape::VResize));
    }

    Cursor::~Cursor()
    {
        if (m_cursors.size() == 0)
            return;

        if (m_cursors.contains(ECursorShape::Arrow) && m_cursors[ECursorShape::Arrow])
            glfwDestroyCursor(m_cursors[ECursorShape::Arrow]);

        if (m_cursors.contains(ECursorShape::IBeam) && m_cursors[ECursorShape::IBeam])
            glfwDestroyCursor(m_cursors[ECursorShape::IBeam]);
        
        if (m_cursors.contains(ECursorShape::CrossHair) && m_cursors[ECursorShape::CrossHair])
            glfwDestroyCursor(m_cursors[ECursorShape::CrossHair]);
        
        if (m_cursors.contains(ECursorShape::Hand) && m_cursors[ECursorShape::Hand])
            glfwDestroyCursor(m_cursors[ECursorShape::Hand]);
        
        if (m_cursors.contains(ECursorShape::HResize) && m_cursors[ECursorShape::HResize])
            glfwDestroyCursor(m_cursors[ECursorShape::HResize]);

        if (m_cursors.contains(ECursorShape::VResize) && m_cursors[ECursorShape::VResize])
            glfwDestroyCursor(m_cursors[ECursorShape::VResize]);

        m_cursors.clear();
    }

    void Cursor::SetCursorPosition(double x, double y)
    {
        if (m_window)
            glfwSetCursorPos(m_window, x, y);
    }

    std::tuple<double, double> Cursor::GetCursorPosition() const
    {
        double x = 0.0;
        double y = 0.0;
     
        if (m_window)
            glfwGetCursorPos(m_window, &x, &y);
        
        return { x, y };
    }

    void Cursor::SetCursorMode(ECursorMode mode)
    {
        if (m_window)
            glfwSetInputMode(m_window, GLFW_CURSOR, static_cast<int>(mode));
    }

    void Cursor::SetCursorShape(ECursorShape cursorShape)
    {
        if (m_window)
            glfwSetCursor(m_window, m_cursors[cursorShape]);
    }
}

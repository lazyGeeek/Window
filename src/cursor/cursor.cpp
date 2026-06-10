#include "window/cursor/cursor.hpp"

#include <GLFW/glfw3.h>

namespace Window::Cursor
{
    Cursor::Cursor(const GLFW& glfw) : m_glfw { glfw }
    {
        m_cursors[ECursorShape::Arrow] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::Arrow));
        m_cursors[ECursorShape::IBeam] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::IBeam));
        m_cursors[ECursorShape::CrossHair] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::CrossHair));
        m_cursors[ECursorShape::Hand] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::Hand));
        m_cursors[ECursorShape::HResize] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::HResize));
        m_cursors[ECursorShape::VResize] =
            glfwCreateStandardCursor(static_cast<int>(ECursorShape::VResize));
    }

    Cursor::~Cursor()
    {
        if (m_cursors.contains(ECursorShape::Arrow) &&
            m_cursors[ECursorShape::Arrow])
            glfwDestroyCursor(m_cursors[ECursorShape::Arrow]);

        if (m_cursors.contains(ECursorShape::IBeam) &&
            m_cursors[ECursorShape::IBeam])
            glfwDestroyCursor(m_cursors[ECursorShape::IBeam]);

        if (m_cursors.contains(ECursorShape::CrossHair) &&
            m_cursors[ECursorShape::CrossHair])
            glfwDestroyCursor(m_cursors[ECursorShape::CrossHair]);

        if (m_cursors.contains(ECursorShape::Hand) &&
            m_cursors[ECursorShape::Hand])
            glfwDestroyCursor(m_cursors[ECursorShape::Hand]);

        if (m_cursors.contains(ECursorShape::HResize) &&
            m_cursors[ECursorShape::HResize])
            glfwDestroyCursor(m_cursors[ECursorShape::HResize]);

        if (m_cursors.contains(ECursorShape::VResize) &&
            m_cursors[ECursorShape::VResize])
            glfwDestroyCursor(m_cursors[ECursorShape::VResize]);
    }

    void Cursor::SetPosition(Utils::PositionDouble pos)
    {
        if (!isWindowValid())
            return;

        glfwSetCursorPos(m_glfw.GetWindow(), pos.X, pos.Y);
    }

    Utils::PositionDouble Cursor::GetPosition() const
    {
        Utils::PositionDouble pos { .X = 0.0, .Y = 0.0 };

        if (!isWindowValid())
            return pos;

        glfwGetCursorPos(m_glfw.GetWindow(), &pos.X, &pos.Y);
        return pos;
    }

    void Cursor::SetMode(ECursorMode mode)
    {
        if (!isWindowValid())
            return;

        glfwSetInputMode(m_glfw.GetWindow(), GLFW_CURSOR,
                         static_cast<int>(mode));
    }

    void Cursor::SetShape(ECursorShape cursorShape)
    {
        if (!isWindowValid())
            return;

        glfwSetCursor(m_glfw.GetWindow(), m_cursors[cursorShape]);
    }

    [[nodiscard]] bool Cursor::isWindowValid() const
    {
        return m_glfw.GetWindow() != nullptr;
    }

} // namespace Window::Cursor

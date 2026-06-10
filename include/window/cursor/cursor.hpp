#pragma once

#include "window/cursor/cursor_mode.hpp"
#include "window/cursor/cursor_shape.hpp"
#include "window/glfw.hpp"
#include "window/utils/non_copyable.hpp"
#include "window/utils/types.hpp"

#include <unordered_map>

struct GLFWcursor;

namespace Window::Cursor
{
    class Cursor : public Utils::NonCopyable
    {
    public:
        explicit Cursor(const GLFW& glfw);
        ~Cursor() override;

        void SetPosition(Utils::PositionDouble pos);
        [[nodiscard]] Utils::PositionDouble GetPosition() const;

        void SetMode(ECursorMode mode);
        void SetShape(ECursorShape cursor);

    private:
        [[nodiscard]] bool isWindowValid() const;

        const GLFW& m_glfw;
        std::unordered_map<ECursorShape, GLFWcursor*> m_cursors;
    };
} // namespace Window::Cursor

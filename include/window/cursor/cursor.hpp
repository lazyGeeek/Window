#pragma once
#ifndef WINDOW_CURSOR_CURSOR_HPP_
#define WINDOW_CURSOR_CURSOR_HPP_

#include "window/cursor/cursor_mode.hpp"
#include "window/cursor/cursor_shape.hpp"
#include "window/utils/non_copyable.hpp"

#include <unordered_map>

struct GLFWwindow;
struct GLFWcursor;

namespace Window::Cursor
{
    class Cursor : public Utils::NonCopyable
    {
    public:
        Cursor(GLFWwindow* window);
        virtual ~Cursor() override;

        void SetPosition(double x, double y);
        std::tuple<double, double> GetPosition() const;

        void SetMode(ECursorMode mode);
        void SetShape(ECursorShape cursor);

    private:
        GLFWwindow* m_window = nullptr;
        std::unordered_map<ECursorShape, GLFWcursor*> m_cursors;
    };
}

#endif // WINDOW_CURSOR_CURSOR_HPP_

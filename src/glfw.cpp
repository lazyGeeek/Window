#include "window/glfw.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

#include "window/monitor.hpp"

#include <format>
#include <stdexcept>

namespace Window
{
    GLFW::GLFW(const WindowInit& windowInit)
    {
        parseInit(windowInit);
        createGLFWWindow();
        bindEventCallbacks();

        AddListener([&, this](Window::Eventing::IEvent& event) {
            if (event.GetEventType() ==
                Window::Eventing::EEventType::WindowMove) {
                const auto& move =
                    dynamic_cast<Eventing::WindowMoveEvent&>(event);
                onMove(move.GetPosition());
            } else if (event.GetEventType() ==
                       Window::Eventing::EEventType::WindowResize) {
                const auto& resize =
                    dynamic_cast<Eventing::WindowResizeEvent&>(event);
                onResize(resize.GetSize());
            }
        });
    }

    GLFW::~GLFW()
    {
        RemoveAllListeners();
        if (m_window) {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
        glfwTerminate();
    }

    void GLFW::parseInit(const WindowInit& windowInit)
    {
        m_title = windowInit.Title;
        m_size = windowInit.Size;
    }

    void GLFW::createGLFWWindow()
    {
        auto errorCallback = [](int code, const char* description) {
            throw std::runtime_error(
                std::format("GLFW ERROR :: Code: ({}) :: Description: {}", code,
                            description));
        };

        glfwSetErrorCallback(errorCallback);

        if (glfwInit() == GLFW_FALSE) {
            glfwTerminate();
            throw std::runtime_error("GLFW ERROR :: Failed to Init GLFW");
        }

#ifdef WINDOW_USE_VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_SAMPLES, static_cast<int>(m_samples));
        glfwWindowHint(GLFW_RESIZABLE, m_resizable);
        glfwWindowHint(GLFW_DECORATED, m_decorated);
        glfwWindowHint(GLFW_FOCUSED, m_focused);
        glfwWindowHint(GLFW_MAXIMIZED, m_maximized);
        glfwWindowHint(GLFW_FLOATING, m_floating);
        glfwWindowHint(GLFW_VISIBLE, m_visible);
        glfwWindowHint(GLFW_AUTO_ICONIFY, m_autoIconify);
        glfwWindowHint(GLFW_REFRESH_RATE, m_refreshRate);

        m_window = glfwCreateWindow(m_size.Width, m_size.Height,
                                    m_title.c_str(), nullptr, nullptr);

        if (!m_window)
            throw std::runtime_error(
                "GLFW ERROR :: Failed to create GLFW window");

        if (m_pos == Utils::PositionInt32 { .X = DONT_CARE, .Y = DONT_CARE })
            glfwGetWindowPos(m_window, &m_pos.X, &m_pos.Y);
        else
            glfwSetWindowPos(m_window, m_pos.X, m_pos.Y);

        glfwSetWindowSizeLimits(m_window, m_minSize.Width, m_minSize.Height,
                                m_maxSize.Width, m_maxSize.Height);

        if (m_fullscreen)
            SetFullscreen(true);

#ifndef WINDOW_USE_VULKAN
        glfwMakeContextCurrent(m_window);
#endif

        glfwSetWindowUserPointer(m_window, this);

        m_monitor = std::make_unique<Monitor>(m_pos);
    }

    void GLFW::bindEventCallbacks()
    {
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto keyCallback = [](GLFWwindow* window, int key,
                              __attribute__((unused)) int scancode, int action,
                              __attribute__((unused)) int mods) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            if (action == GLFW_PRESS) {
                Eventing::KeyPressEvent pressEvent(
                    static_cast<Inputs::EKey>(key));
                current->Invoke(pressEvent);
            }

            if (action == GLFW_RELEASE) {
                Eventing::KeyReleaseEvent releaseEvent(
                    static_cast<Inputs::EKey>(key));
                current->Invoke(releaseEvent);
            }
        };

        glfwSetKeyCallback(m_window, keyCallback);

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto mouseCallback = [](GLFWwindow* window, int button, int action,
                                __attribute__((unused)) int mods) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            if (action == GLFW_PRESS) {
                Eventing::MousePressEvent pressEvent(
                    static_cast<Inputs::EMouseButton>(button));
                current->Invoke(pressEvent);
            }

            if (action == GLFW_RELEASE) {
                Eventing::MouseReleaseEvent releaseEvent(
                    static_cast<Inputs::EMouseButton>(button));
                current->Invoke(releaseEvent);
            }
        };

        glfwSetMouseButtonCallback(m_window, mouseCallback);

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::MouseMoveEvent moveEvent({ .X = x, .Y = y });
            current->Invoke(moveEvent);
        };

        glfwSetCursorPosCallback(m_window, cursorMoveCallback);

        auto scrollCallback = [](GLFWwindow* window, double offsetX,
                                 double offsetY) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::MouseScrollEvent scrollEvent(
                { .X = offsetX, .Y = offsetY });
            current->Invoke(scrollEvent);
        };

        glfwSetScrollCallback(m_window, scrollCallback);

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto resizeCallback = [](GLFWwindow* window, int width, int height) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::WindowResizeEvent resizeEvent(
                { .Width = width, .Height = height });
            current->Invoke(resizeEvent);
        };

        glfwSetWindowSizeCallback(m_window, resizeCallback);

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto framebufferResizeCallback = [](GLFWwindow* window, int width,
                                            int height) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::FramebufferResizeEvent resizeEvent(
                { .Width = width, .Height = height });
            current->Invoke(resizeEvent);
        };

        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        auto moveCallback = [](GLFWwindow* window, int x, int y) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::WindowMoveEvent moveEvent({ .X = x, .Y = y });
            current->Invoke(moveEvent);
        };

        glfwSetWindowPosCallback(m_window, moveCallback);

        auto iconifyCallback = [](GLFWwindow* window, int iconified) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            if (iconified == GLFW_TRUE) {
                Eventing::WindowMinimizeEvent minEvent;
                current->Invoke(minEvent);
            }

            if (iconified == GLFW_FALSE) {
                Eventing::WindowMaximizeEvent maxEvent;
                current->Invoke(maxEvent);
            }
        };

        glfwSetWindowIconifyCallback(m_window, iconifyCallback);

        auto focusCallback = [](GLFWwindow* window, int focused) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            if (focused == GLFW_TRUE) {
                Eventing::WindowGainFocusEvent gainEvent;
                current->Invoke(gainEvent);
            }

            if (focused == GLFW_FALSE) {
                Eventing::WindowLostFocusEvent lostEvent;
                current->Invoke(lostEvent);
            }
        };

        glfwSetWindowFocusCallback(m_window, focusCallback);

        auto closeCallback = [](GLFWwindow* window) {
            GLFW* current =
                static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (!current)
                return;

            Eventing::WindowCloseEvent closeEvent;
            current->Invoke(closeEvent);
        };

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    void GLFW::onResize(Utils::SizeInt32 size)
    {
        if (m_fullscreen)
            return;

        m_size = size;
    }

    void GLFW::onMove(Utils::PositionInt32 pos)
    {
        if (m_fullscreen)
            return;

        m_pos = pos;

        if (m_monitor)
            m_monitor->UpdateMonitor(m_pos);
    }

    void GLFW::CloseWindow()
    {
        glfwSetWindowShouldClose(m_window, true);
    }

    void GLFW::MakeCurrentContext() const
    {
        glfwMakeContextCurrent(m_window);
    }

    void GLFW::ClearCurrentContext() const
    {
        glfwMakeContextCurrent(nullptr);
    }

    void GLFW::SetSize(Utils::SizeInt32 size)
    {
        glfwSetWindowSize(m_window, size.Width, size.Height);
    }

    void GLFW::SetPosition(Utils::PositionInt32 pos)
    {
        glfwSetWindowPos(m_window, pos.X, pos.Y);
    }

    void GLFW::SetMinimumSize(Utils::SizeInt32 size)
    {
        m_minSize = size;

        glfwSetWindowSizeLimits(m_window, m_minSize.Width, m_minSize.Height,
                                m_maxSize.Width, m_maxSize.Height);
    }

    void GLFW::SetMaximumSize(Utils::SizeInt32 size)
    {
        m_maxSize = size;

        glfwSetWindowSizeLimits(m_window, m_minSize.Width, m_minSize.Height,
                                m_maxSize.Width, m_maxSize.Height);
    }

    void GLFW::SetFullscreen(bool value)
    {
        m_fullscreen = value;

        if (m_fullscreen && m_monitor) {
            VideoMode mode = m_monitor->GetVideoMode();
            Utils::PositionInt32 pos = m_monitor->GetPosition();
            glfwSetWindowMonitor(m_window, m_monitor->GetMonitor(), pos.X,
                                 pos.Y, mode.Size.Width, mode.Size.Height,
                                 m_refreshRate);
        } else {
            glfwSetWindowMonitor(m_window, nullptr, m_pos.X, m_pos.Y,
                                 m_size.Width, m_size.Height, m_refreshRate);
        }
    }

    void GLFW::SetTitle(const std::string& title)
    {
        m_title = title;
        glfwSetWindowTitle(m_window, title.c_str());
    }

    void GLFW::SetVsync(bool vsync)
    {
        m_vsync = vsync;
        glfwSwapInterval(vsync ? 1 : 0);
    }

    void GLFW::SetShouldClose(bool value) const
    {
        glfwSetWindowShouldClose(m_window, value);
    }

    void GLFW::Minimize() const
    {
        glfwIconifyWindow(m_window);
    }

    void GLFW::Maximize() const
    {
        glfwMaximizeWindow(m_window);
    }

    void GLFW::Restore() const
    {
        glfwRestoreWindow(m_window);
    }

    void GLFW::Hide() const
    {
        glfwHideWindow(m_window);
    }

    void GLFW::Show() const
    {
        glfwShowWindow(m_window);
    }

    void GLFW::Focus() const
    {
        glfwFocusWindow(m_window);
    }

    bool GLFW::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void GLFW::ToggleFullscreen()
    {
        SetFullscreen(!IsFullscreen());
    }

    bool GLFW::IsFullscreen() const
    {
        return m_fullscreen;
    }

    bool GLFW::IsHidden() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_VISIBLE) == GLFW_FALSE;
    }

    bool GLFW::IsVisible() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_VISIBLE) == GLFW_TRUE;
    }

    bool GLFW::IsMaximized() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_TRUE;
    }

    bool GLFW::IsMinimized() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_FALSE;
    }

    bool GLFW::IsFocused() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE;
    }

    bool GLFW::IsResizable() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE) == GLFW_TRUE;
    }

    bool GLFW::IsDecorated() const
    {
        return glfwGetWindowAttrib(m_window, GLFW_DECORATED) == GLFW_TRUE;
    }

#ifndef WINDOW_USE_VULKAN
    void GLFW::SwapBuffers() const
    {
        glfwSwapBuffers(m_window);
    }
#endif

    void GLFW::PollEvents() const
    {
        glfwPollEvents();
    }

    std::string GLFW::GetTitle() const
    {
        return m_title;
    }

    Utils::SizeInt32 GLFW::GetSize() const
    {
        Utils::SizeInt32 size { .Width = DONT_CARE, .Height = DONT_CARE };
        glfwGetWindowSize(m_window, &size.Width, &size.Height);
        return size;
    }

    Utils::SizeInt32 GLFW::GetMinimumSize() const
    {
        return m_minSize;
    }

    Utils::SizeInt32 GLFW::GetMaximumSize() const
    {
        return m_maxSize;
    }

    Utils::PositionInt32 GLFW::GetPosition() const
    {
        Utils::PositionInt32 pos { .X = DONT_CARE, .Y = DONT_CARE };

        glfwGetWindowPos(m_window, &pos.X, &pos.Y);
        return pos;
    }

    Utils::SizeInt32 GLFW::GetFramebufferSize() const
    {
        Utils::SizeInt32 size { .Width = DONT_CARE, .Height = DONT_CARE };
        glfwGetFramebufferSize(m_window, &size.Width, &size.Height);
        return size;
    }

    bool GLFW::HasVsync() const
    {
        return m_vsync;
    }

    GLFWwindow* GLFW::GetWindow() const
    {
        return m_window;
    }
} // namespace Window

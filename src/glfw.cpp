#include "window/glfw.hpp"
#include "window/eventing/input_events.hpp"
#include "window/eventing/window_events.hpp"

#include "window/monitor.hpp"

#include <stdexcept>

namespace Window
{
    GLFW::GLFW(WindowInit windowInit)
    {
        parseInit(windowInit);
        createGLFWWindow();
        bindEventCallbacks();

        AddListener([&, this](Window::Eventing::IEvent& event)
        {
            if (event.GetEventType() == Window::Eventing::EEventType::WindowMove)
            {
                const auto& move = dynamic_cast<Eventing::WindowMoveEvent&>(event);
                onMove(move.GetPosX(), move.GetPosY());
            }
            else if (event.GetEventType() == Window::Eventing::EEventType::WindowResize)
            {
                const auto& resize = dynamic_cast<Eventing::WindowResizeEvent&>(event);
                onResize(resize.GetWidth(), resize.GetHeight());
            }
        });
    }

    GLFW::~GLFW()
    {
        removeAllListeners();
        if (m_window)
        {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
        glfwTerminate();
    }

    void GLFW::parseInit(const WindowInit& windowInit)
    {
        m_title  = windowInit.Title;
        m_width  = windowInit.Width;
        m_height = windowInit.Height;
    }

    void GLFW::createGLFWWindow()
    {
        auto errorCallback = [](int code, const char* description)
        {
            throw std::runtime_error(description);
        };

        glfwSetErrorCallback(errorCallback);
        
        if (glfwInit() == GLFW_FALSE)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to Init GLFW");
        }

#ifdef WINDOW_USE_VULKAN
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_SAMPLES,      m_samples);
        glfwWindowHint(GLFW_RESIZABLE,    m_resizable);
        glfwWindowHint(GLFW_DECORATED,    m_decorated);
        glfwWindowHint(GLFW_FOCUSED,      m_focused);
        glfwWindowHint(GLFW_MAXIMIZED,    m_maximized);
        glfwWindowHint(GLFW_FLOATING,     m_floating);
        glfwWindowHint(GLFW_VISIBLE,      m_visible);
        glfwWindowHint(GLFW_AUTO_ICONIFY, m_autoIconify);
        glfwWindowHint(GLFW_REFRESH_RATE, m_refreshRate);
        glfwWindowHint(GLFW_SAMPLES,      m_samples);

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (!m_window)
            throw std::runtime_error("[GLFW] Failed to create GLFW window");

        if (m_posX == DONT_CARE && m_posY == DONT_CARE)
            glfwGetWindowPos(m_window, &m_posX, &m_posY);
        else
            glfwSetWindowPos(m_window, m_posX, m_posY);

        glfwSetWindowSizeLimits(m_window, m_minWidth, m_minHeight, m_maxWidth, m_maxHeight);

        if (m_fullscreen)
            SetFullscreen(true);

#ifndef WINDOW_USE_VULKAN
        glfwMakeContextCurrent(m_window);
#endif

        glfwSetWindowUserPointer(m_window, this);

        m_monitor = std::make_unique<Monitor>(m_posX, m_posY);
    }

    void GLFW::bindEventCallbacks()
    {
        auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::KeyPressEvent pressEvent(static_cast<Inputs::EKey>(key));
                    current->invoke(pressEvent);
                }

                if (action == GLFW_RELEASE)
                {
                    Eventing::KeyReleaseEvent releaseEvent(static_cast<Inputs::EKey>(key));
                    current->invoke(releaseEvent);
                }
            }
        };

        glfwSetKeyCallback(m_window, keyCallback);

        auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::MousePressEvent pressEvent(static_cast<Inputs::EMouseButton>(button));
                    current->invoke(pressEvent);
                }
                
                if (action == GLFW_RELEASE)
                {
                    Eventing::MouseReleaseEvent releaseEvent(static_cast<Inputs::EMouseButton>(button));
                    current->invoke(releaseEvent);
                }
            }
        };

        glfwSetMouseButtonCallback(m_window, mouseCallback);

        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::MouseMoveEvent moveEvent(x, y);
                current->invoke(moveEvent);
            }
        };

        glfwSetCursorPosCallback(m_window, cursorMoveCallback);

        auto scrollCallback = [](GLFWwindow* window, double offsetX, double offsetY)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));
            
            if (current)
            {
                Eventing::MouseScrollEvent scrollEvent(offsetX, offsetY);
                current->invoke(scrollEvent);
            }
        };

        glfwSetScrollCallback(m_window, scrollCallback);

        auto resizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowResizeEvent resizeEvent(width, height);
                current->invoke(resizeEvent);
            }
        };

        glfwSetWindowSizeCallback(m_window, resizeCallback);

        auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::FramebufferResizeEvent resizeEvent(width, height);
                current->invoke(resizeEvent);
            }
        };

        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);

        auto moveCallback = [](GLFWwindow* window, int x, int y)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowMoveEvent moveEvent(x, y);
                current->invoke(moveEvent);
            }
        };

        glfwSetWindowPosCallback(m_window, moveCallback);

        auto iconifyCallback = [](GLFWwindow* window, int iconified)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (iconified == GLFW_TRUE)
                {
                    Eventing::WindowMinimizeEvent minEvent;
                    current->invoke(minEvent);
                }

                if (iconified == GLFW_FALSE)
                {
                    Eventing::WindowMaximizeEvent maxEvent;
                    current->invoke(maxEvent);
                }
            }
        };

        glfwSetWindowIconifyCallback(m_window, iconifyCallback);

        auto focusCallback = [](GLFWwindow* window, int focused)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (focused == GLFW_TRUE)
                {
                    Eventing::WindowGainFocusEvent gainEvent;
                    current->invoke(gainEvent);
                }

                if (focused == GLFW_FALSE)
                {
                    Eventing::WindowLostFocusEvent lostEvent;
                    current->invoke(lostEvent);
                }
            }
        };

        glfwSetWindowFocusCallback(m_window, focusCallback);

        auto closeCallback = [](GLFWwindow* window)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowCloseEvent closeEvent;
                current->invoke(closeEvent);
            }
        };

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    void GLFW::onResize(int32_t width, int32_t height)
    {
        if (m_fullscreen)
            return;

        m_width = width;
        m_height = height;
    }

    void GLFW::onMove(int32_t x, int32_t y)
    {
        if (m_fullscreen)
            return;

        m_posX = x;
        m_posY = y;
        
        if (m_monitor)
            m_monitor->UpdateMonitor(m_posX, m_posY);
    }

    void GLFW::CloseWindow()
    {
        // if (m_window)
        {
            glfwSetWindowShouldClose(m_window, true);
            // glfwDestroyWindow(m_window);
            // m_window = nullptr;
        }
    }

    void GLFW::MakeCurrentContext() const
    {
        glfwMakeContextCurrent(m_window);
    }

    void GLFW::ClearCurrentContext() const
    {
        glfwMakeContextCurrent(nullptr);
    }

    void GLFW::SetSize(int32_t width, int32_t height)
    {
        glfwSetWindowSize(m_window, width, height);
    }

    void GLFW::SetPosition(int32_t x, int32_t y)
    {
        glfwSetWindowPos(m_window, x, y);
    }

    void GLFW::SetMinimumSize(int32_t width, int32_t height)
    {
        m_minWidth = width;
        m_minHeight = height;

        glfwSetWindowSizeLimits(m_window,
            m_minWidth, m_minHeight,
            m_maxWidth, m_maxHeight);
    }

    void GLFW::SetMaximumSize(int32_t width, int32_t height)
    {
        m_maxWidth = width;
        m_maxHeight = height;

        glfwSetWindowSizeLimits(m_window,
            m_minWidth, m_minHeight,
            m_maxWidth, m_maxHeight);
    }

    void GLFW::SetFullscreen(bool value)
    {
        m_fullscreen = value;

        if (m_fullscreen && m_monitor)
        {
            VideoMode mode = m_monitor->GetVideoMode();
            const auto [posX, posY] = m_monitor->GetPosition();
            glfwSetWindowMonitor(m_window, m_monitor->GetMonitor(),
                                 posX, posY, mode.Width, mode.Height,
                                 m_refreshRate);
        }
        else
            glfwSetWindowMonitor(m_window, nullptr,
                                 m_posX, m_posY,
                                 m_width, m_height,
                                 m_refreshRate);

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

    std::tuple<int32_t, int32_t> GLFW::GetSize() const
    {
        int32_t width = -1;
        int32_t height = -1;
        glfwGetWindowSize(m_window, &width, &height);
        return {width, height};
    }

    std::tuple<int32_t, int32_t> GLFW::GetMinimumSize() const
    {
        return { m_minWidth, m_minHeight };
    }

    std::tuple<int32_t, int32_t> GLFW::GetMaximumSize() const
    {
        return { m_maxWidth, m_maxHeight };
    }

    std::tuple<int32_t, int32_t> GLFW::GetPosition() const
    {
        int32_t x = -1;
        int32_t y = -1;
        glfwGetWindowPos(m_window, &x, &y);
        return { x, y };
    }

    std::tuple<int32_t, int32_t> GLFW::GetFramebufferSize() const
    {
        int32_t width = -1;
        int32_t height = -1;
        glfwGetFramebufferSize(m_window, &width, &height);
        return { width, height };
    }

    bool GLFW::HasVsync() const
    {
        return m_vsync;
    }

    GLFWwindow* GLFW::GetWindow() const
    {
        return m_window;
    }
}
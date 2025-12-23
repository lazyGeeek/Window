#include "window/glfw.hpp"
#include "window/inputs/input_manager.hpp"

#include "window/eventing/window_events.hpp"
#include "window/eventing/input_events.hpp"

#include <stdexcept>

#include <iostream>

namespace Window
{
    GLFW::GLFW(const WindowInit& windowInit, bool fullscreen)
    {
        parseInit(windowInit, fullscreen);
        createGLFWWindow();

        bindKeyCallback();
        bindMouseCallback();
        bindCursorMoveCallback();
        bindScrollCallback();
        bindIconifyCallback();
        bindCloseCallback();
        bindResizeCallback();
        bindFramebufferResizeCallback();
        bindMoveCallback();
        bindFocusCallback();

        m_inputManager = std::make_unique<Inputs::InputManager>(this);
    }

    GLFW::~GLFW()
    {
        if (m_inputManager)
            m_inputManager = nullptr;

        CloseWindow();
        glfwTerminate();
    }

    void GLFW::parseInit(const WindowInit& windowInit, bool fullscreen)
    {
        m_title = windowInit.Title;
        
        m_width     = windowInit.Width;
        m_height    = windowInit.Height;
        m_minWidth  = windowInit.MinWidth;
        m_minHeight = windowInit.MinHeight;
        m_maxWidth  = windowInit.MaxWidth;
        m_maxHeight = windowInit.MaxHeight;
        m_posX      = windowInit.PosX;
        m_posY      = windowInit.PosY;
        
        m_fullscreen  = windowInit.Fullscreen;
        m_decorated   = windowInit.Decorated;
        m_resizable   = windowInit.Resizable;
        m_focused     = windowInit.Focused;
        m_maximized   = windowInit.Maximized;
        m_floating    = windowInit.Floating;
        m_visible     = windowInit.Visible;
        m_autoIconify = windowInit.AutoIconify;
        
        m_refreshRate = windowInit.RefreshRate;
        m_samples = windowInit.Samples;
        
        m_fullscreen = fullscreen;
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

        glfwWindowHint(GLFW_SAMPLES, m_samples);

        GLFWmonitor* selectedMonitor = nullptr;

        if (m_fullscreen)
            selectedMonitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_RESIZABLE,    m_resizable);
        glfwWindowHint(GLFW_DECORATED,    m_decorated);
        glfwWindowHint(GLFW_FOCUSED,      m_focused);
        glfwWindowHint(GLFW_MAXIMIZED,    m_maximized);
        glfwWindowHint(GLFW_FLOATING,     m_floating);
        glfwWindowHint(GLFW_VISIBLE,      m_visible);
        glfwWindowHint(GLFW_AUTO_ICONIFY, m_autoIconify);
        glfwWindowHint(GLFW_REFRESH_RATE, m_refreshRate);
        glfwWindowHint(GLFW_SAMPLES,      m_samples);

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), selectedMonitor, nullptr);

        if (!m_window)
            throw std::runtime_error("Failed to create GLFW window");

        if (m_posX == DONT_CARE && m_posY == DONT_CARE)
            glfwGetWindowPos(m_window, &m_posX, &m_posY);
        else
            glfwSetWindowPos(m_window, m_posX, m_posY);

        glfwSetWindowSizeLimits(m_window, m_minWidth, m_minHeight, m_maxWidth, m_maxHeight);

        if (m_fullscreen)
            SetFullscreen(true);

        glfwSetWindowUserPointer(m_window, this);

#ifndef WINDOW_USE_VULKAN
        glfwMakeContextCurrent(m_window);
#endif
    }

    void GLFW::bindKeyCallback() const
    {
        auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::KeyPressedEvent pressedEvent(static_cast<Inputs::EKey>(key));
                    current->Events.Invoke(pressedEvent);
                }

                if (action == GLFW_RELEASE)
                {
                    Eventing::KeyReleasedEvent releasedEvent(static_cast<Inputs::EKey>(key));
                    current->Events.Invoke(releasedEvent);
                }
            }
        };

        glfwSetKeyCallback(m_window, keyCallback);
    }

    void GLFW::bindMouseCallback() const
    {
        auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                {
                    Eventing::MousePressedEvent pressedEvent(static_cast<Inputs::EMouseButton>(button));
                    current->Events.Invoke(pressedEvent);
                }
                
                if (action == GLFW_RELEASE)
                {
                    Eventing::MouseReleasedEvent releasedEvent(static_cast<Inputs::EMouseButton>(button));
                    current->Events.Invoke(releasedEvent);
                }
            }
        };

        glfwSetMouseButtonCallback(m_window, mouseCallback);
    }

    void GLFW::bindCursorMoveCallback() const
    {
        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::MouseMovedEvent movedEvent(x, y);
                current->Events.Invoke(movedEvent);
            }
        };

        glfwSetCursorPosCallback(m_window, cursorMoveCallback);
    }

    void GLFW::bindScrollCallback() const
    {
        auto scrollCallback = [](GLFWwindow* window, double offsetX, double offsetY)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));
            
            if (current)
            {
                Eventing::MouseScrolledEvent scrolledEvent(offsetX, offsetY);
                current->Events.Invoke(scrolledEvent);
            }
        };

        glfwSetScrollCallback(m_window, scrollCallback);
    }

    void GLFW::bindResizeCallback() const
    {
        auto resizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                current->onResize(width, height);
                Eventing::WindowResizeEvent resizeEvent(width, height);
                current->Events.Invoke(resizeEvent);
            }
        };

        glfwSetWindowSizeCallback(m_window, resizeCallback);
    }

    void GLFW::bindFramebufferResizeCallback() const
    {
        auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::FramebufferResizeEvent resizeEvent(width, height);
                current->Events.Invoke(resizeEvent);
            }
        };

        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    }

    void GLFW::bindMoveCallback() const
    {
        auto moveCallback = [](GLFWwindow* window, int x, int y)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                current->onMove(x, y);
                Eventing::WindowMoveEvent moveEvent(x, y);
                current->Events.Invoke(moveEvent);
            }
        };

        glfwSetWindowPosCallback(m_window, moveCallback);
    }

    void GLFW::bindIconifyCallback() const
    {
        auto iconifyCallback = [](GLFWwindow* window, int iconified)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (iconified == GLFW_TRUE)
                {
                    Eventing::WindowMinimizeEvent minEvent;
                    current->Events.Invoke(minEvent);
                }

                if (iconified == GLFW_FALSE)
                {
                    Eventing::WindowMaximizeEvent maxEvent;
                    current->Events.Invoke(maxEvent);
                }
            }
        };

        glfwSetWindowIconifyCallback(m_window, iconifyCallback);
    }

    void GLFW::bindFocusCallback() const
    {
        auto focusCallback = [](GLFWwindow* window, int focused)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (focused == GLFW_TRUE)
                {
                    Eventing::WindowGainFocusEvent gainEvent;
                    current->Events.Invoke(gainEvent);
                }

                if (focused == GLFW_FALSE)
                {
                    Eventing::WindowLostFocusEvent lostEvent;
                    current->Events.Invoke(lostEvent);
                }
            }
        };

        glfwSetWindowFocusCallback(m_window, focusCallback);
    }

    void GLFW::bindCloseCallback() const
    {
        auto closeCallback = [](GLFWwindow* window)
        {
            GLFW* current = static_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                Eventing::WindowCloseEvent closeEvent;
                current->Events.Invoke(closeEvent);
            }
        };

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    void GLFW::onResize(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
    }

    void GLFW::onMove(int32_t x, int32_t y)
    {
        m_posX = x;
        m_posY = y;
    }

    void GLFW::CloseWindow()
    {
        Events.RemoveAllListeners();

        if (m_window)
        {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
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

    Inputs::InputManager& GLFW::getInputManager() const
    {
        if (!m_inputManager)
            throw std::runtime_error("Input Manager Destroyed");

        return *m_inputManager.get();
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
        if (value)
        {
            m_fullscreen = true;

            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwSetWindowMonitor
            (
                m_window,
                value ? glfwGetPrimaryMonitor() : nullptr,
                m_posX,
                m_posY,
                mode->width,
                mode->height,
                m_refreshRate
            );
        }
        else
        {
            m_fullscreen = true;

            glfwSetWindowMonitor
            (
                m_window,
                value ? glfwGetPrimaryMonitor() : nullptr,
                m_posX,
                m_posY,
                m_width,
                m_height,
                m_refreshRate
            );
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
#include "window/glfw.hpp"
#include "window/inputs/input_manager.hpp"

#include <stdexcept>

#include <iostream>

namespace Window
{
    GLFW::GLFW(const Settings::WindowSettings& windowSettings, bool fullscreen) :
        m_settings{ windowSettings },
        m_fullscreen { fullscreen }
    {
        createGLFWWindow(windowSettings);

        bindKeyCallback();
        bindMouseCallback();
        bindCursorMoveCallback();
        bindIconifyCallback();
        bindCloseCallback();
        bindResizeCallback();
        bindFramebufferResizeCallback();
        bindMoveCallback();
        bindFocusCallback();

        ResizeEvent.AddListener(std::bind(&GLFW::onResize, this, std::placeholders::_1, std::placeholders::_2));
        MoveEvent.AddListener(std::bind(&GLFW::onMove, this, std::placeholders::_1, std::placeholders::_2));

        m_inputManager = std::make_unique<Inputs::InputManager>(this);
    }

    GLFW::~GLFW()
    {
        if (m_inputManager)
            m_inputManager = nullptr;

        CloseWindow();
        glfwTerminate();
    }

    void GLFW::createGLFWWindow(const Settings::WindowSettings& windowSettings)
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

        glfwWindowHint(GLFW_SAMPLES, windowSettings.Samples);

        GLFWmonitor* selectedMonitor = nullptr;

        if (m_fullscreen)
            selectedMonitor = glfwGetPrimaryMonitor();

        glfwWindowHint(GLFW_RESIZABLE,    windowSettings.Resizable);
        glfwWindowHint(GLFW_DECORATED,    windowSettings.Decorated);
        glfwWindowHint(GLFW_FOCUSED,      windowSettings.Focused);
        glfwWindowHint(GLFW_MAXIMIZED,    windowSettings.Maximized);
        glfwWindowHint(GLFW_FLOATING,     windowSettings.Floating);
        glfwWindowHint(GLFW_VISIBLE,      windowSettings.Visible);
        glfwWindowHint(GLFW_AUTO_ICONIFY, windowSettings.AutoIconify);
        glfwWindowHint(GLFW_REFRESH_RATE, windowSettings.RefreshRate);
        glfwWindowHint(GLFW_SAMPLES,      windowSettings.Samples);

        m_window = glfwCreateWindow(m_settings.Width, m_settings.Height, m_settings.Title.c_str(), selectedMonitor, nullptr);

        if (!m_window)
            throw std::runtime_error("Failed to create GLFW window");

        if (m_settings.Y == Settings::WindowSettings::DONT_CARE &&
            m_settings.Y == Settings::WindowSettings::DONT_CARE)
            glfwGetWindowPos(m_window, &m_settings.X, &m_settings.Y);
        else
            glfwSetWindowPos(m_window, m_settings.X, m_settings.Y);

        glfwSetWindowSizeLimits(m_window, m_settings.MinWidth, m_settings.MinHeight,
                m_settings.MaxWidth, m_settings.MaxHeight);

        if (m_settings.Fullscreen)
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
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                    current->m_inputManager->KeyPressedEvent.Invoke(static_cast<Inputs::EKey>(key));

                if (action == GLFW_RELEASE)
                    current->m_inputManager->KeyReleasedEvent.Invoke(static_cast<Inputs::EKey>(key));
            }
        };

        glfwSetKeyCallback(m_window, keyCallback);
    }

    void GLFW::bindMouseCallback() const
    {
        auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (action == GLFW_PRESS)
                    current->m_inputManager->MouseButtonPressedEvent.Invoke(static_cast<Inputs::EMouseButton>(button));

                if (action == GLFW_RELEASE)
                    current->m_inputManager->MouseButtonReleasedEvent.Invoke(static_cast<Inputs::EMouseButton>(button));
            }
        };

        glfwSetMouseButtonCallback(m_window, mouseCallback);
    }

    void GLFW::bindCursorMoveCallback() const
    {
        auto cursorMoveCallback = [](GLFWwindow* window, double x, double y)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->m_inputManager->CursorMoveEvent.Invoke(x, y);
        };

        glfwSetCursorPosCallback(m_window, cursorMoveCallback);
    }

    void GLFW::bindResizeCallback() const
    {
        auto resizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->ResizeEvent.Invoke(width, height);
        };

        glfwSetWindowSizeCallback(m_window, resizeCallback);
    }

    void GLFW::bindFramebufferResizeCallback() const
    {
        auto framebufferResizeCallback = [](GLFWwindow* window, int width, int height)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->FramebufferResizeEvent.Invoke(width, height);
        };

        glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
    }

    void GLFW::bindMoveCallback() const
    {
        auto moveCallback = [](GLFWwindow* window, int x, int y)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->MoveEvent.Invoke(x, y);
        };

        glfwSetWindowPosCallback(m_window, moveCallback);
    }

    void GLFW::bindIconifyCallback() const
    {
        auto iconifyCallback = [](GLFWwindow* window, int iconified)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (iconified == GLFW_TRUE)
                    current->MinimizeEvent.Invoke();

                if (iconified == GLFW_FALSE)
                    current->MaximizeEvent.Invoke();
            }
        };

        glfwSetWindowIconifyCallback(m_window, iconifyCallback);
    }

    void GLFW::bindFocusCallback() const
    {
        auto focusCallback = [](GLFWwindow* window, int focused)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
            {
                if (focused == GLFW_TRUE)
                    current->GainFocusEvent.Invoke();

                if (focused == GLFW_FALSE)
                    current->LostFocusEvent.Invoke();
            }
        };

        glfwSetWindowFocusCallback(m_window, focusCallback);
    }

    void GLFW::bindCloseCallback() const
    {
        auto closeCallback = [](GLFWwindow* window)
        {
            GLFW* current = reinterpret_cast<GLFW*>(glfwGetWindowUserPointer(window));

            if (current)
                current->CloseEvent.Invoke();
        };

        glfwSetWindowCloseCallback(m_window, closeCallback);
    }

    void GLFW::onResize(int32_t width, int32_t height)
    {
        m_settings.Width = width;
        m_settings.Height = height;
    }

    void GLFW::onMove(int32_t x, int32_t y)
    {
        m_settings.X = x;
        m_settings.Y = y;
    }

    void GLFW::CloseWindow()
    {
        ResizeEvent.RemoveAllListeners();
        MoveEvent.RemoveAllListeners();
        FramebufferResizeEvent.RemoveAllListeners();

        MinimizeEvent.RemoveAllListeners();
        MaximizeEvent.RemoveAllListeners();
        RestoreEvent.RemoveAllListeners();
        LostFocusEvent.RemoveAllListeners();
        GainFocusEvent.RemoveAllListeners();
        CloseEvent.RemoveAllListeners();

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
        m_settings.MinWidth = width;
        m_settings.MinHeight = height;
        glfwSetWindowSizeLimits(m_window,
            m_settings.MinWidth, m_settings.MinHeight,
            m_settings.MaxWidth, m_settings.MaxHeight);
    }

    void GLFW::SetMaximumSize(int32_t width, int32_t height)
    {
        m_settings.MaxWidth = width;
        m_settings.MaxHeight = height;
        glfwSetWindowSizeLimits(m_window,
            m_settings.MinWidth, m_settings.MinHeight,
            m_settings.MaxWidth, m_settings.MaxHeight);
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
                m_settings.X,
                m_settings.Y,
                mode->width,
                mode->height,
                m_settings.RefreshRate
            );
        }
        else
        {
            m_fullscreen = true;

            glfwSetWindowMonitor
            (
                m_window,
                value ? glfwGetPrimaryMonitor() : nullptr,
                m_settings.X,
                m_settings.Y,
                m_settings.Width,
                m_settings.Height,
                m_settings.RefreshRate
            );
        }
    }

    void GLFW::SetTitle(const std::string& title)
    {
        m_settings.Title = title;
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
        return m_settings.Title;
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
        return { m_settings.MinWidth, m_settings.MinHeight };
    }

    std::tuple<int32_t, int32_t> GLFW::GetMaximumSize() const
    {
        return { m_settings.MaxWidth, m_settings.MaxHeight };
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
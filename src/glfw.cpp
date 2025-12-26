#include "window/glfw.hpp"
#include "window/eventing/event_manager.hpp"
#include "window/eventing/window_events.hpp"

#include <stdexcept>

namespace Window
{
    GLFW::GLFW(WindowInit windowInit)
    {
        parseInit(windowInit);
        createGLFWWindow();

        m_eventManager = std::make_unique<Eventing::EventManager>(m_window);
        m_eventManager->AddListener([&, this](Window::Eventing::IEvent& event)
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
            else if (event.GetEventType() == Window::Eventing::EEventType::WindowClose)
            {
                CloseWindow();
            }
        });
    }

    GLFW::~GLFW()
    {
        CloseWindow();
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
        if (m_eventManager)
            m_eventManager = nullptr;

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

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowMonitor
        (
            m_window,
            m_fullscreen ? glfwGetPrimaryMonitor() : nullptr,
            m_posX,
            m_posY,
            m_fullscreen ? mode->width : m_width,
            m_fullscreen ? mode->height : m_height,
            m_refreshRate
        );
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
#pragma once
#ifndef WINDOW_GLFW_HPP_
#define WINDOW_GLFW_HPP_

#include <memory>
#include <unordered_map>

#ifdef WINDOW_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include "window/utils/event.hpp"
#include "window/eventing/event_dispatcher.hpp"

namespace Window
{
    namespace Inputs { class InputManager; }

    struct WindowInit
    {
        std::string Title = "";

        int32_t Width     = 1280;
        int32_t Height    = 720;
        int32_t MinWidth  = -1;
        int32_t MinHeight = -1;
        int32_t MaxWidth  = -1;
        int32_t MaxHeight = -1;
        int32_t PosX      = -1;
        int32_t PosY      = -1;

        bool Fullscreen  = false;
        bool Decorated   = true;
        bool Resizable   = true;
        bool Focused     = true;
        bool Maximized   = false;
        bool Floating    = false;
        bool Visible     = true;
        bool AutoIconify = true;

        int32_t RefreshRate = -1;
        uint32_t Samples = 4;
    };

    class GLFW
    {
    public:
        GLFW(const WindowInit& windowInit, bool fullscreen = false);
        virtual ~GLFW();

        GLFW(const GLFW& other)             = delete;
        GLFW(GLFW&& other)                  = delete;
        GLFW& operator=(const GLFW& other)  = delete;
        GLFW& operator=(const GLFW&& other) = delete;

        void SetSize(int32_t width, int32_t height);
        void SetPosition(int32_t x, int32_t y);
        void SetMinimumSize(int32_t width, int32_t height);
        void SetMaximumSize(int32_t width, int32_t height);
        void SetFullscreen(bool value);
        void SetTitle(const std::string& title);
        void SetVsync(bool vsync);
        void SetShouldClose(bool value) const;

        void Minimize() const;
        void Maximize() const;
        void Restore() const;
        void Hide() const;
        void Show() const;
        void Focus() const;

        bool ShouldClose() const;

        void ToggleFullscreen();

        bool IsFullscreen() const;
        bool IsHidden() const;
        bool IsVisible() const;
        bool IsMaximized() const;
        bool IsMinimized() const;
        bool IsFocused() const;
        bool IsResizable() const;
        bool IsDecorated() const;

#ifndef WINDOW_USE_VULKAN
        void SwapBuffers() const;
#endif
        void PollEvents() const;

        std::string GetTitle() const;

        std::tuple<int32_t, int32_t> GetSize() const;
        std::tuple<int32_t, int32_t> GetMinimumSize() const;
        std::tuple<int32_t, int32_t> GetMaximumSize() const;
        std::tuple<int32_t, int32_t> GetPosition() const;
        std::tuple<int32_t, int32_t> GetFramebufferSize() const;

        bool HasVsync() const;

        GLFWwindow* GetWindow() const;

        Inputs::InputManager& getInputManager() const;

        void CloseWindow();

        void MakeCurrentContext() const;
        void ClearCurrentContext() const;

        Eventing::Dispatcher Events;

        static const inline int32_t DONT_CARE = -1;

    private:
        void parseInit(const WindowInit& windowInit, bool fullscreen);
        void createGLFWWindow();

        void bindKeyCallback() const;
        void bindMouseCallback() const;
        void bindCursorMoveCallback() const;
        void bindScrollCallback() const;
        void bindResizeCallback() const;
        void bindFramebufferResizeCallback() const;
        void bindMoveCallback() const;
        void bindIconifyCallback() const;
        void bindFocusCallback() const;
        void bindCloseCallback() const;

        void onResize(int32_t width, int32_t height);
        void onMove(int32_t x, int32_t y);

        GLFWwindow* m_window = nullptr;
        std::unique_ptr<Inputs::InputManager> m_inputManager;

        std::string m_title = "";

        int32_t m_width     = 1280;
        int32_t m_height    = 720;
        int32_t m_minWidth  = DONT_CARE;
        int32_t m_minHeight = DONT_CARE;
        int32_t m_maxWidth  = DONT_CARE;
        int32_t m_maxHeight = DONT_CARE;
        int32_t m_posX      = DONT_CARE;
        int32_t m_posY      = DONT_CARE;

        bool m_fullscreen  = false;
        bool m_decorated   = true;
        bool m_resizable   = true;
        bool m_focused     = true;
        bool m_maximized   = false;
        bool m_floating    = false;
        bool m_visible     = true;
        bool m_autoIconify = true;

        int32_t m_refreshRate = DONT_CARE;
        uint32_t m_samples = 4;

        bool m_vsync = false;
    };
}

#endif // WINDOW_GLFW_HPP_

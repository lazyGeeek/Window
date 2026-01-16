#pragma once
#ifndef WINDOW_GLFW_HPP_
#define WINDOW_GLFW_HPP_

#include <memory>
#include <unordered_map>

#ifdef WINDOW_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include "window/eventing/event_dispatcher.hpp"
#include "window/utils/non_copyable.hpp"

int Add(int a, int b) { return a + b; }

namespace Window
{
    class Monitor;

    struct WindowInit
    {
        std::string Title = "";

        int32_t Width  = 1280;
        int32_t Height = 720;
    };

    class GLFW : public Utils::NonCopyable, public Eventing::Dispatcher
    {
    public:
        GLFW(WindowInit windowInit = { });
        ~GLFW() override;

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

        void CloseWindow();

        void MakeCurrentContext() const;
        void ClearCurrentContext() const;

        static const inline int32_t DONT_CARE = -1;

    private:
        void parseInit(const WindowInit& windowInit);
        void createGLFWWindow();
        void bindEventCallbacks();

        void onResize(int32_t width, int32_t height);
        void onMove(int32_t x, int32_t y);

        GLFWwindow* m_window = nullptr;
        std::unique_ptr<Monitor> m_monitor = nullptr;

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

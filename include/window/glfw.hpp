#pragma once

#include <memory>
#include <string>

#ifdef WINDOW_USE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#include "window/eventing/event_dispatcher.hpp"
#include "window/monitor.hpp"
#include "window/utils/non_copyable.hpp"
#include "window/utils/types.hpp"

namespace Window
{
    struct WindowInit
    {
        std::string Title = "";

        int32_t Width = 1280;
        int32_t Height = 720;
    };

    class GLFW : public Utils::NonCopyable, public Eventing::Dispatcher
    {
    public:
        GLFW(WindowInit windowInit = {});
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

        [[nodiscard]] bool ShouldClose() const;

        void ToggleFullscreen();

        [[nodiscard]] bool IsFullscreen() const;
        [[nodiscard]] bool IsHidden() const;
        [[nodiscard]] bool IsVisible() const;
        [[nodiscard]] bool IsMaximized() const;
        [[nodiscard]] bool IsMinimized() const;
        [[nodiscard]] bool IsFocused() const;
        [[nodiscard]] bool IsResizable() const;
        [[nodiscard]] bool IsDecorated() const;

#ifndef WINDOW_USE_VULKAN
        void SwapBuffers() const;
#endif
        void PollEvents() const;

        [[nodiscard]] std::string GetTitle() const;

        [[nodiscard]] std::tuple<int32_t, int32_t> GetSize() const;
        [[nodiscard]] std::tuple<int32_t, int32_t> GetMinimumSize() const;
        [[nodiscard]] std::tuple<int32_t, int32_t> GetMaximumSize() const;
        [[nodiscard]] std::tuple<int32_t, int32_t> GetPosition() const;
        [[nodiscard]] Utils::SizeInt32 GetFramebufferSize() const;

        [[nodiscard]] bool HasVsync() const;

        [[nodiscard]] GLFWwindow* GetWindow() const;

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

        int32_t m_width = 1280;
        int32_t m_height = 720;
        int32_t m_minWidth = DONT_CARE;
        int32_t m_minHeight = DONT_CARE;
        int32_t m_maxWidth = DONT_CARE;
        int32_t m_maxHeight = DONT_CARE;
        int32_t m_posX = DONT_CARE;
        int32_t m_posY = DONT_CARE;

        bool m_fullscreen = false;
        bool m_decorated = true;
        bool m_resizable = true;
        bool m_focused = true;
        bool m_maximized = false;
        bool m_floating = false;
        bool m_visible = true;
        bool m_autoIconify = true;

        int32_t m_refreshRate = DONT_CARE;
        uint32_t m_samples = 4;

        bool m_vsync = false;
    };
} // namespace Window

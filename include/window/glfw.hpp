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
        Utils::SizeInt32 Size { .Width = 1280, .Height = 720 };
    };

    class GLFW : public Utils::NonCopyable, public Eventing::Dispatcher
    {
    public:
        GLFW(const WindowInit& windowInit = {});
        ~GLFW() override;

        void SetSize(Utils::SizeInt32 size);
        void SetPosition(Utils::PositionInt32 pos);
        void SetMinimumSize(Utils::SizeInt32 size);
        void SetMaximumSize(Utils::SizeInt32 size);
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

        [[nodiscard]] Utils::SizeInt32 GetSize() const;
        [[nodiscard]] Utils::SizeInt32 GetMinimumSize() const;
        [[nodiscard]] Utils::SizeInt32 GetMaximumSize() const;
        [[nodiscard]] Utils::PositionInt32 GetPosition() const;
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

        void onResize(Utils::SizeInt32 size);
        void onMove(Utils::PositionInt32 pos);

        GLFWwindow* m_window = nullptr;
        std::unique_ptr<Monitor> m_monitor = nullptr;

        std::string m_title = "";

        Utils::SizeInt32 m_size { .Width = 1280, .Height = 720 };
        Utils::SizeInt32 m_minSize { .Width = DONT_CARE, .Height = DONT_CARE };
        Utils::SizeInt32 m_maxSize { .Width = DONT_CARE, .Height = DONT_CARE };
        Utils::PositionInt32 m_pos { .X = DONT_CARE, .Y = DONT_CARE };

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

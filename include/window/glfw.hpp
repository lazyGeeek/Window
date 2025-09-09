#pragma once
#ifndef WINDOW_GLFW_HPP_
#define WINDOW_GLFW_HPP_

#include <memory>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "window/settings/window_settings.hpp"
#include "window/utils/event.hpp"

namespace Window
{
    namespace Inputs { class InputManager; }

    class GLFW
    {
    public:
        GLFW(const Settings::WindowSettings& windowSettings, bool fullscreen = false);
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

        void SwapBuffers() const;
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

        Utils::Event<int32_t, int32_t> ResizeEvent;
        Utils::Event<int32_t, int32_t> MoveEvent;
        Utils::Event<int32_t, int32_t> FramebufferResizeEvent;

        Utils::Event<> MinimizeEvent;
        Utils::Event<> MaximizeEvent;
        Utils::Event<> RestoreEvent;
        Utils::Event<> LostFocusEvent;
        Utils::Event<> GainFocusEvent;
        Utils::Event<> CloseEvent;

    private:
        void createGLFWWindow(const Settings::WindowSettings& windowSettings);

        void bindKeyCallback() const;
        void bindMouseCallback() const;
        void bindCursorMoveCallback() const;
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

        Settings::WindowSettings m_settings;
        bool m_fullscreen = false;
        bool m_vsync = false;
    };
}

#endif // WINDOW_GLFW_HPP_

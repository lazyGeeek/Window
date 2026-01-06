#pragma once
#ifndef WINDOW_MONITOR_HPP_
#define WINDOW_MONITOR_HPP_

#include "window/utils/non_copyable.hpp"

#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>

struct GLFWmonitor;
struct GLFWvidmode;
struct GLFWwindow;

namespace Window
{
    struct VideoMode
    {
        int32_t Width;
        int32_t Height;
        int32_t RedBits;
        int32_t GreenBits;
        int32_t BlueBits;
        int32_t RefreshRate;
    };

    struct GammaRamp
    {
        uint16_t* Red;
        uint16_t* Green;
        uint16_t* Blue;
        uint32_t  Size;
    };

    struct MonitorInfo
    {
        int32_t PosX;
        int32_t PosY;
        int32_t Width;
        int32_t Height;
        int32_t RefreshRate;
    };

    class Monitor : public Utils::NonCopyable
    {
    public:
        Monitor(GLFWmonitor* monitor);
        Monitor(int32_t posX, int32_t posY);

        static GLFWmonitor* GetPrimaryMonitor();
        GLFWmonitor* GetMonitor() const;

        void UpdateMonitor(int32_t posX, int32_t posY);

        bool IsPrimary() const;

        std::tuple<int32_t, int32_t> GetWorkareaSize() const;
        std::tuple<int32_t, int32_t> GetWorkareaPosition() const;
        std::tuple<int32_t, int32_t> GetSize() const;
        std::tuple<float, float>     GetContentScale() const;
        std::tuple<int32_t, int32_t> GetPosition() const;

        std::string GetName() const;
        std::vector<VideoMode> GetVideoModes() const;
        VideoMode GetVideoMode() const;
        GammaRamp GetGammaRamp() const;
        
        void SetGammaRamp(const GammaRamp& gammaRamp) const;

    private:
        VideoMode videoModeConverter(const GLFWvidmode& mode) const;

        GLFWmonitor* m_monitor = nullptr;
    };
}

#endif // WINDOW_MONITOR_HPP_

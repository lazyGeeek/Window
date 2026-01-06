#include "window/monitor.hpp"

#include <GLFW/glfw3.h>

namespace Window
{
    Monitor::Monitor(GLFWmonitor* monitor) : m_monitor { monitor } { }

    Monitor::Monitor(int32_t posX, int32_t posY)
    {
        UpdateMonitor(posX, posY);
    }

    GLFWmonitor* Monitor::GetPrimaryMonitor()
    {
        return glfwGetPrimaryMonitor();
    }

    void Monitor::UpdateMonitor(int32_t posX, int32_t posY)
    {
        int count = 0;
        GLFWmonitor** monitor = glfwGetMonitors(&count);

        if (!count)
            return;

        m_monitor = monitor[0];

        for (size_t i = 0; i < count; ++i)
        {
            int x = 0;
            int y = 0;
            int width = 0;
            int height = 0;

            glfwGetMonitorWorkarea(monitor[i], &x, &y, &width, &height);

            if (posX >= x && posY >= y &&
                (x + width >= posX) && (y + height >= posY))
            {
                m_monitor = monitor[i];
                break;
            }
        }
    }

    bool Monitor::IsPrimary() const
    {
        return m_monitor == glfwGetPrimaryMonitor();
    }

    GLFWmonitor* Monitor::GetMonitor() const
    {
        return m_monitor;
    }

    std::tuple<int32_t, int32_t> Monitor::GetWorkareaSize() const
    {
        int32_t width = 0;
        int32_t height = 0;
        glfwGetMonitorWorkarea(m_monitor, nullptr, nullptr, &width, &height);
        return { width, height };
    }

    std::tuple<int32_t, int32_t> Monitor::GetWorkareaPosition() const
    {
        int32_t posX = 0;
        int32_t posY = 0;
        glfwGetMonitorWorkarea(m_monitor, &posX, &posY, nullptr, nullptr);
        return { posX, posY };
    }

    std::tuple<int32_t, int32_t> Monitor::GetSize() const
    {
        int32_t width = 0;
        int32_t height = 0;
        glfwGetMonitorPhysicalSize(m_monitor, &width, &height);
        return { width, height };
    }

    std::tuple<float, float> Monitor::GetContentScale() const
    {
        float scaleX = 0.0f;
        float scaleY = 0.0f;
        glfwGetMonitorContentScale(m_monitor, &scaleX, &scaleY);
        return { scaleX, scaleY };
    }

    std::tuple<int32_t, int32_t> Monitor::GetPosition() const
    {
        int32_t posX = 0;
        int32_t posY = 0;
        glfwGetMonitorPos(m_monitor, &posX, &posY);
        return { posX, posY };
    }

    std::string Monitor::GetName() const
    {
        return glfwGetMonitorName(m_monitor);
    }

    std::vector<VideoMode> Monitor::GetVideoModes() const
    {
        int32_t videoModeCount = 0;
        const GLFWvidmode* videoModes = glfwGetVideoModes(m_monitor, &videoModeCount);
        
        size_t videoModeSize = static_cast<size_t>(videoModeCount);
        std::vector<VideoMode> modes(videoModeSize);
        
        for (uint32_t i = 0; i < videoModeSize; ++i)
            modes[i] = videoModeConverter(videoModes[i]);
        
        return modes;
    }

    VideoMode Monitor::GetVideoMode() const
    {
        const GLFWvidmode* videoMode = glfwGetVideoMode(m_monitor);
        return videoModeConverter(*videoMode);
    }

    GammaRamp Monitor::GetGammaRamp() const
    {
        const GLFWgammaramp* gamma = glfwGetGammaRamp(m_monitor);
        return
        {
            .Red = gamma->red,
            .Green = gamma->green,
            .Blue = gamma->blue,
            .Size = gamma->size
        };
    }

    void Monitor::SetGammaRamp(const GammaRamp &gammaRamp) const
    {
        GLFWgammaramp ramp =
        {
            .red = gammaRamp.Red,
            .green = gammaRamp.Green,
            .blue = gammaRamp.Blue,
            .size = gammaRamp.Size
        };
        glfwSetGammaRamp(m_monitor, &ramp);
    }

    VideoMode Monitor::videoModeConverter(const GLFWvidmode& mode) const
    {
        return
        {
            .Width = mode.width,
            .Height = mode.height,
            .RedBits = mode.redBits,
            .GreenBits = mode.greenBits,
            .BlueBits = mode.blueBits,
            .RefreshRate = mode.refreshRate
        };
    }
}

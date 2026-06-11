#include "window/monitor.hpp"

#include <GLFW/glfw3.h>

namespace Window
{
    Monitor::Monitor(GLFWmonitor* monitor) : m_monitor { monitor }
    { }

    Monitor::Monitor(Utils::PositionInt32 pos)
    {
        UpdateMonitor(pos);
    }

    GLFWmonitor* Monitor::GetPrimaryMonitor()
    {
        return glfwGetPrimaryMonitor();
    }

    void Monitor::UpdateMonitor(Utils::PositionInt32 pos)
    {
        int count = 0;
        GLFWmonitor** monitor = glfwGetMonitors(&count);

        if (!count)
            return;

        m_monitor = monitor[0];

        for (int i = 0; i < count; ++i) {
            int x = 0;
            int y = 0;
            int width = 0;
            int height = 0;

            glfwGetMonitorWorkarea(monitor[i], &x, &y, &width, &height);

            if (pos.X >= x && pos.Y >= y && (x + width >= pos.X) &&
                (y + height >= pos.Y)) {
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

    Utils::SizeInt32 Monitor::GetWorkareaSize() const
    {
        Utils::SizeInt32 size { .Width = 0, .Height = 0 };
        glfwGetMonitorWorkarea(m_monitor, nullptr, nullptr, &size.Width,
                               &size.Height);
        return size;
    }

    Utils::PositionInt32 Monitor::GetWorkareaPosition() const
    {
        Utils::PositionInt32 pos { .X = 0, .Y = 0 };
        glfwGetMonitorWorkarea(m_monitor, &pos.X, &pos.Y, nullptr, nullptr);
        return pos;
    }

    Utils::SizeInt32 Monitor::GetSize() const
    {
        Utils::SizeInt32 size { .Width = 0, .Height = 0 };
        glfwGetMonitorPhysicalSize(m_monitor, &size.Width, &size.Height);
        return size;
    }

    Utils::ScaleFloat Monitor::GetContentScale() const
    {
        Utils::ScaleFloat scale { .X = 0.0f, .Y = 0.0f };
        glfwGetMonitorContentScale(m_monitor, &scale.X, &scale.Y);
        return scale;
    }

    Utils::PositionInt32 Monitor::GetPosition() const
    {
        Utils::PositionInt32 pos { .X = 0, .Y = 0 };
        glfwGetMonitorPos(m_monitor, &pos.X, &pos.Y);
        return pos;
    }

    std::string Monitor::GetName() const
    {
        return glfwGetMonitorName(m_monitor);
    }

    std::vector<VideoMode> Monitor::GetVideoModes() const
    {
        int32_t videoModeCount = 0;
        const GLFWvidmode* videoModes =
            glfwGetVideoModes(m_monitor, &videoModeCount);

        auto videoModeSize = static_cast<size_t>(videoModeCount);
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
        return { .Red = gamma->red,
                 .Green = gamma->green,
                 .Blue = gamma->blue,
                 .Size = gamma->size };
    }

    void Monitor::SetGammaRamp(const GammaRamp& gammaRamp) const
    {
        GLFWgammaramp ramp = { .red = gammaRamp.Red,
                               .green = gammaRamp.Green,
                               .blue = gammaRamp.Blue,
                               .size = gammaRamp.Size };
        glfwSetGammaRamp(m_monitor, &ramp);
    }

    VideoMode Monitor::videoModeConverter(const GLFWvidmode& mode) const
    {
        return { .Size = Utils::SizeInt32 { .Width = mode.width,
                                            .Height = mode.height },
                 .RedBits = mode.redBits,
                 .GreenBits = mode.greenBits,
                 .BlueBits = mode.blueBits,
                 .RefreshRate = mode.refreshRate };
    }
} // namespace Window

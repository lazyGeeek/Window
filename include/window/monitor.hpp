#pragma once

#include "window/utils/non_copyable.hpp"
#include "window/utils/types.hpp"

#include <string>
#include <vector>

struct GLFWmonitor;
struct GLFWvidmode;
struct GLFWwindow;

namespace Window
{
    struct VideoMode
    {
        Utils::SizeInt32 Size;
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
        uint32_t Size;
    };

    struct MonitorInfo
    {
        Utils::PositionInt32 Pos;
        Utils::SizeInt32 Size;
        int32_t RefreshRate;
    };

    class Monitor : public Utils::NonCopyable
    {
    public:
        Monitor(GLFWmonitor* monitor);
        Monitor(Utils::PositionInt32 pos);

        static GLFWmonitor* GetPrimaryMonitor();
        [[nodiscard]] GLFWmonitor* GetMonitor() const;

        void UpdateMonitor(Utils::PositionInt32 pos);

        [[nodiscard]] bool IsPrimary() const;

        [[nodiscard]] Utils::SizeInt32 GetWorkareaSize() const;
        [[nodiscard]] Utils::PositionInt32 GetWorkareaPosition() const;
        [[nodiscard]] Utils::SizeInt32 GetSize() const;
        [[nodiscard]] Utils::ScaleFloat GetContentScale() const;
        [[nodiscard]] Utils::PositionInt32 GetPosition() const;

        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] std::vector<VideoMode> GetVideoModes() const;
        [[nodiscard]] VideoMode GetVideoMode() const;
        [[nodiscard]] GammaRamp GetGammaRamp() const;

        void SetGammaRamp(const GammaRamp& gammaRamp) const;

    private:
        [[nodiscard]] VideoMode
        videoModeConverter(const GLFWvidmode& mode) const;

        GLFWmonitor* m_monitor = nullptr;
    };
} // namespace Window

#pragma once
#ifndef WINDOW_SETTINGS_WINDOW_SETTINGS_HPP_
#define WINDOW_SETTINGS_WINDOW_SETTINGS_HPP_

#include <string>

namespace Window::Settings
{
    struct WindowSettings
    {
        static const int32_t DONT_CARE = -1;

        std::string Title = "";

        int32_t Width     = 1280;
        int32_t Height    = 720;
        int32_t MinWidth  = DONT_CARE;
        int32_t MinHeight = DONT_CARE;
        int32_t MaxWidth  = DONT_CARE;
        int32_t MaxHeight = DONT_CARE;
        int32_t X         = DONT_CARE;
        int32_t Y         = DONT_CARE;

        bool Fullscreen  = false;
        bool Decorated   = true;
        bool Resizable   = true;
        bool Focused     = true;
        bool Maximized   = false;
        bool Floating    = false;
        bool Visible     = true;
        bool AutoIconify = true;

        int32_t RefreshRate = DONT_CARE;
        uint32_t Samples = 4;
    };
}

#endif // WINDOW_SETTINGS_WINDOW_SETTINGS_HPP_

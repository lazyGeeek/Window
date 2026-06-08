#pragma once

#include <cstdint>

namespace Window::Inputs
{
    enum class EMouseButton : std::int8_t
    {
        Unknown = -1,
        B1 = 0,
        B2 = 1,
        B3 = 2,
        B4 = 3,
        B5 = 4,
        B6 = 5,
        B7 = 6,
        B8 = 7,
        Left = 0,
        Right = 1,
        Middle = 2
    };
} // namespace Window::Inputs

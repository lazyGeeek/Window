#pragma once

#include <cstdint>

namespace Window::Inputs
{
    enum class EKeyState : std::uint8_t
    {
        Released,
        Pressed
    };
} // namespace Window::Inputs

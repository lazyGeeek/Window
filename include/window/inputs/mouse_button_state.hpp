#pragma once

#include <cstdint>

namespace Window::Inputs
{
    enum class EMouseButtonState : std::uint8_t
    {
        Released,
        Pressed
    };
} // namespace Window::Inputs

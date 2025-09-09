#pragma once
#ifndef WINDOW_CURSOR_CURSOR_SHAPE_HPP_
#define WINDOW_CURSOR_CURSOR_SHAPE_HPP_

#include <stdint.h>

namespace Window::Cursor
{
    enum class ECursorShape
    {
        Arrow     = 0x00036001,
        IBeam     = 0x00036002,
        CrossHair = 0x00036003,
        Hand      = 0x00036004,
        HResize   = 0x00036005,
        VResize   = 0x00036006
    };
}

#endif // WINDOW_CURSOR_CURSOR_SHAPE_HPP_

#pragma once
#ifndef WINDOW_CURSOR_CURSOR_MODE_HPP_
#define WINDOW_CURSOR_CURSOR_MODE_HPP_

#include <stdint.h>

namespace Window::Cursor
{
    enum class ECursorMode
    {
        Normal   = 0x00034001,
        Disabled = 0x00034003,
        Hidden   = 0x00034002
    };
}

#endif // WINDOW_CURSOR_CURSOR_MODE_HPP_

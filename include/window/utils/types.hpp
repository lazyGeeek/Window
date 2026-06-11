#pragma once

#include "window/utils/comparators.hpp"

namespace Window::Utils
{
    template <SizeElement T>
    struct Size
    {
        T Width;
        T Height;

        bool operator==(const Size& other) const
        {
            return Comparator<T>(Width, other.Width) &&
                   Comparator<T>(Height, other.Height);
        }
    };

    template <SizeElement T>
    struct Position
    {
        T X;
        T Y;

        bool operator==(const Position& other) const
        {
            return Comparator<T>(X, other.X) && Comparator<T>(Y, other.Y);
        }
    };

    template <SizeElement T>
    struct Offset
    {
        T X;
        T Y;

        bool operator==(const Offset& other) const
        {
            return Comparator<T>(X, other.X) && Comparator<T>(Y, other.Y);
        }
    };

    template <SizeElement T>
    struct Scale
    {
        T X;
        T Y;

        bool operator==(const Scale& other) const
        {
            return Comparator<T>(X, other.X) && Comparator<T>(Y, other.Y);
        }
    };

    using SizeInt32 = Utils::Size<int32_t>;
    using PositionInt32 = Utils::Position<int32_t>;
    using PositionDouble = Utils::Position<double>;
    using OffsetDouble = Utils::Offset<double>;
    using ScaleFloat = Utils::Scale<float>;
} // namespace Window::Utils

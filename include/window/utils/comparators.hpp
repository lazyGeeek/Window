#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>

namespace Window::Utils
{
    template <typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

    // Supports operator==
    template <typename A, typename B = A>
    concept EqualityComparableWith = requires(A a, B b) {
        { a == b } -> std::convertible_to<bool>;
    };

    // Constraint that T is either numeric or equality-comparable with itself
    template <typename T>
    concept SizeElement = Numeric<T> || EqualityComparableWith<T, T>;

    // Integral equality
    template <SizeElement T>
    bool Comparator(const T& lhs, const T& rhs)
        requires std::integral<T>
    {
        return lhs == rhs;
    }

    // Floating-point equality
    template <SizeElement T>
    bool Comparator(const T& lhs, const T& rhs, T epsilon = 1e-9)
        requires std::floating_point<T>
    {
        T diff = std::fabs(lhs - rhs);
        if (diff <= epsilon)
            return true;

        T maxVal = std::max(std::fabs(lhs), std::fabs(rhs));

        return diff <= epsilon * maxVal;
    }

    // Fallback for non-numeric but equality-comparable types
    template <SizeElement T>
    bool Comparator(const T& lhs, const T& rhs)
        requires(!Numeric<T> && EqualityComparableWith<T, T>)
    {
        return lhs == rhs;
    }
} // namespace Window::Utils

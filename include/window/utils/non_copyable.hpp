#pragma once
#ifndef WINDOW_UTILS_NON_COPYABLE_HPP_
#define WINDOW_UTILS_NON_COPYABLE_HPP_

namespace Window::Utils
{
    class NonCopyable
    {
    public:
        NonCopyable()          = default;
        virtual ~NonCopyable() = default;

        NonCopyable(const NonCopyable& other)            = delete;
        NonCopyable(NonCopyable&& other)                 = delete;
        NonCopyable& operator=(const NonCopyable& other) = delete;
        NonCopyable& operator=(NonCopyable&& other)      = delete;
    };
}

#endif // WINDOW_UTILS_NON_COPYABLE_HPP_

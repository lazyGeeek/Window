#include <gtest/gtest.h>

#include "window/utils/non_copyable.hpp"

namespace Window::Utils
{
    class CopyableProbe : public NonCopyable
    {
    public:
        CopyableProbe() = default;
    };

    static_assert(!std::is_copy_constructible_v<CopyableProbe>);
    static_assert(!std::is_copy_assignable_v<CopyableProbe>);
    static_assert(!std::is_move_constructible_v<CopyableProbe>);
    static_assert(!std::is_move_assignable_v<CopyableProbe>);
    static_assert(std::is_default_constructible_v<CopyableProbe>);

    TEST(NonCopyableTest, CanConstructAndDestroy)
    {
        CopyableProbe probe;
        (void)probe;
        SUCCEED();
    }
}

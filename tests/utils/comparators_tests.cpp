#include <gtest/gtest.h>

#include "window/utils/comparators.hpp"

namespace Window::Utils
{
    // Custom non-numeric type that supports operator==
    struct MyComparable
    {
        int a;
        bool operator==(MyComparable const& other) const noexcept
        {
            return a == other.a;
        }
    };

    TEST(IntegralComparator, Integers)
    {
        EXPECT_TRUE(Comparator<int>(5, 5));
        EXPECT_TRUE(Comparator<long>(-10L, -10L));
        EXPECT_TRUE(Comparator<int>(0, 0));

        EXPECT_FALSE(Comparator<int>(5, 6));
        EXPECT_FALSE(Comparator<unsigned int>(0u, 1u));
    }

    TEST(FloatingComparator, Doubles)
    {
        EXPECT_TRUE(Comparator<double>(1.2345, 1.2345));
        EXPECT_TRUE(Comparator<double>(0.0, 0.0));
        EXPECT_TRUE(Comparator<float>(1.2f, 1.2f));
        EXPECT_TRUE(Comparator<float>(0.0f, 0.0f));

        EXPECT_FALSE(Comparator<double>(1.2345, 2.3456));
        EXPECT_FALSE(Comparator<double>(0.0, 2.3456));
        EXPECT_FALSE(Comparator<float>(1.2f, 2.3f));
        EXPECT_FALSE(Comparator<float>(0.0f, 2.3f));
    }

    TEST(FloatingComparator, WithinAbsoluteEpsilon)
    {
        double x = 1.000000001;
        double y = 1.000000002;

        EXPECT_TRUE(Comparator<double>(x, y, 1e-8));
    }

    TEST(FloatingComparator, OutsideAbsoluteEpsilonButWithinRelative)
    {
        double x = 1e9 + 1.0;
        double y = 1e9 + 2.0;

        // absolute diff = 1.0 which may be > epsilon 1e-9, but relative check
        // should pass with a larger epsilon
        EXPECT_TRUE(Comparator<double>(x, y, 1e-9));
        // with relative check using maxVal ~1e9, diff <=
        // eps*maxVal -> 1 <= 1e0 -> true
    }

    TEST(FloatingComparator, OutsideBothEpsilons)
    {
        double x = 1.0;
        double y = 2.0;

        EXPECT_FALSE(Comparator<double>(x, y, 1e-9));
    }

    TEST(FloatingComparator, CustomEpsilonFloat)
    {
        float x = 1000.0f;
        float y = 1000.1f;

        EXPECT_FALSE(Comparator<float>(x, y, 1e-6f));
        EXPECT_TRUE(Comparator<float>(x, y, 1e-3f));
    }

    TEST(FloatingComparator, NaNHandling)
    {
        double nan = std::numeric_limits<double>::quiet_NaN();
        double val = 1.0;

        // NaN comparisons should be false because arithmetic yields NaN
        // differences and comparisons with NaN are false
        EXPECT_FALSE(Comparator<double>(nan, nan));
        EXPECT_FALSE(Comparator<double>(nan, val));
        EXPECT_FALSE(Comparator<double>(val, nan));
    }

    TEST(NonNumericComparable, CustomType)
    {
        MyComparable x { .a = 42 };
        MyComparable y { .a = 42 };
        MyComparable z { .a = 43 };

        EXPECT_TRUE(Comparator<MyComparable>(x, y));
        EXPECT_FALSE(Comparator<MyComparable>(x, z));
    }

} // namespace Window::Utils

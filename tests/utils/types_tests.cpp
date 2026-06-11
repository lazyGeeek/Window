#include <gtest/gtest.h>

#include "window/utils/types.hpp"

namespace Window::Utils
{
    TEST(SizeTest, IntEquality)
    {
        Size<int> x { 3, 4 };
        Size<int> y { 3, 4 };
        Size<int> z { 5, 6 };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    TEST(PositionTest, UnsignedEquality)
    {
        Position<uint32_t> x { 4u, 6u };
        Position<uint32_t> y { 4u, 6u };
        Position<uint32_t> z { 8u, 9u };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    TEST(OffsetTest, LongEquality)
    {
        Offset<long> x { 5l, 6l };
        Offset<long> y { 5l, 6l };
        Offset<long> z { 7l, 9l };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    TEST(SizeTest, DoubleEquality)
    {
        Size<double> x { 1.5, 2.5 };
        Size<double> y { 1.5, 2.5 };
        Size<double> z { 4.5, 5.3 };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    TEST(PositionTest, FloatEquality)
    {
        Position<float> x { 2.5f, 3.3f };
        Position<float> y { 2.5f, 3.3f };
        Position<float> z { 5.3f, 8.5f };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    TEST(ScaleTest, FloatEquality)
    {
        Scale<float> x { 2.5f, 3.3f };
        Scale<float> y { 2.5f, 3.3f };
        Scale<float> z { 5.3f, 8.5f };

        EXPECT_TRUE(x == y);
        EXPECT_FALSE(x == z);
    }

    struct EqLike
    {
        int v;
        friend bool operator==(EqLike x, EqLike y)
        {
            return x.v == y.v;
        }
    };

    TEST(SizeTest, CustomEqualityType)
    {
        Size<EqLike> sx { { 1 }, { 2 } };
        Size<EqLike> sy { { 1 }, { 2 } };
        Size<EqLike> sz { { 2 }, { 3 } };

        EXPECT_TRUE(sx == sy);
        EXPECT_FALSE(sx == sz);

        Position<EqLike> px { { 1 }, { 2 } };
        Position<EqLike> py { { 1 }, { 2 } };
        Position<EqLike> pz { { 2 }, { 3 } };

        EXPECT_TRUE(px == py);
        EXPECT_FALSE(px == pz);

        Offset<EqLike> ox { { 1 }, { 2 } };
        Offset<EqLike> oy { { 1 }, { 2 } };
        Offset<EqLike> oz { { 2 }, { 3 } };

        EXPECT_TRUE(ox == oy);
        EXPECT_FALSE(ox == oz);

        Scale<EqLike> scx { { 1 }, { 2 } };
        Scale<EqLike> scy { { 1 }, { 2 } };
        Scale<EqLike> scz { { 2 }, { 3 } };

        EXPECT_TRUE(scx == scy);
        EXPECT_FALSE(scx == scz);
    }

    static_assert(std::is_same_v<Size<int>, Size<int>>);       // numeric
    static_assert(std::is_same_v<Size<EqLike>, Size<EqLike>>); // has operator==

    static_assert(std::is_same_v<Position<long>, Position<long>>);
    static_assert(std::is_same_v<Position<EqLike>, Position<EqLike>>);

    static_assert(std::is_same_v<Offset<float>, Offset<float>>);
    static_assert(std::is_same_v<Offset<EqLike>, Offset<EqLike>>);

    static_assert(std::is_same_v<Scale<float>, Scale<float>>);
    static_assert(std::is_same_v<Scale<EqLike>, Scale<EqLike>>);

    template <typename T, typename = void>
    struct is_size_instantiable : std::false_type
    {
    };

    template <typename T>
    struct is_size_instantiable<T, std::void_t<Size<T>>> : std::true_type
    {
    };

    struct NoEq
    {
        int a; /* no operator== */
    };

    static_assert(!is_size_instantiable<NoEq>::value,
                  "Size<NoEq> should not be instantiable");

    template <typename T, typename = void>
    struct is_position_instantiable : std::false_type
    {
    };

    template <typename T>
    struct is_position_instantiable<T, std::void_t<Position<T>>>
        : std::true_type
    {
    };

    static_assert(!is_position_instantiable<NoEq>::value,
                  "Position<NoEq> should not be instantiable");

    template <typename T, typename = void>
    struct is_offset_instantiable : std::false_type
    {
    };

    template <typename T>
    struct is_offset_instantiable<T, std::void_t<Offset<T>>> : std::true_type
    {
    };

    static_assert(!is_offset_instantiable<NoEq>::value,
                  "Offset<NoEq> should not be instantiable");

    template <typename T, typename = void>
    struct is_scale_instantiable : std::false_type
    {
    };

    template <typename T>
    struct is_scale_instantiable<T, std::void_t<Scale<T>>> : std::true_type
    {
    };

    static_assert(!is_scale_instantiable<NoEq>::value,
                  "Scale<NoEq> should not be instantiable");

} // namespace Window::Utils

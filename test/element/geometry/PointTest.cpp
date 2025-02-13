#include "geometry/Point.h"

#include <gtest/gtest.h>

class PointTest : public testing::Test
{
protected:
    static constexpr float DEFAULT_X = 3;
    static constexpr float DEFAULT_Y = 4;
};

TEST_F(PointTest, initialize)
{
    constexpr element::Point p1(DEFAULT_X, DEFAULT_Y);
    constexpr element::Point p2{.x = DEFAULT_X, .y = DEFAULT_Y};
    const auto [x, y](p1);

    ASSERT_EQ(p1.x, DEFAULT_X);
    ASSERT_EQ(p1.y, DEFAULT_Y);
    ASSERT_EQ(p2.x, DEFAULT_X);
    ASSERT_EQ(p2.y, DEFAULT_Y);
    ASSERT_EQ(x, DEFAULT_X);
    ASSERT_EQ(y, DEFAULT_Y);
}

TEST_F(PointTest, equality)
{
    constexpr element::Point p1(DEFAULT_X, DEFAULT_Y);
    constexpr element::Point p2(DEFAULT_X, DEFAULT_Y);
    constexpr element::Point p3(DEFAULT_X + 1, DEFAULT_Y);
    constexpr element::Point p4(DEFAULT_X, DEFAULT_Y + 1);

    ASSERT_EQ(p1, p2);
    ASSERT_NE(p1, p3);
    ASSERT_NE(p1, p4);
}

TEST_F(PointTest, addition)
{
    constexpr element::Point p1(DEFAULT_X, DEFAULT_Y);
    constexpr element::Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p1 + p2, element::Point(DEFAULT_X * 2 + 1, DEFAULT_Y * 2 + 1));
}

TEST_F(PointTest, subtraction)
{
    constexpr element::Point p1(DEFAULT_X, DEFAULT_Y);
    constexpr element::Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p2 - p1, element::Point(1, 1));
}
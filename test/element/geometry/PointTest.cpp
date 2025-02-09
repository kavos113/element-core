#include "geometry/Point.h"

#include <gtest/gtest.h>

class PointTest : public ::testing::Test
{
protected:
    static constexpr float DEFAULT_X = 3;
    static constexpr float DEFAULT_Y = 4;
};

TEST_F(PointTest, initialize)
{
    element::Point p1(DEFAULT_X, DEFAULT_Y);
    element::Point p2{.x = DEFAULT_X, .y = DEFAULT_Y};
    element::Point p3(p1);

    ASSERT_EQ(p1, element::Point(DEFAULT_X, DEFAULT_Y));
    ASSERT_EQ(p2, element::Point(DEFAULT_X, DEFAULT_Y));
    ASSERT_EQ(p3, element::Point(DEFAULT_X, DEFAULT_Y));
}

TEST_F(PointTest, equality)
{
    element::Point p1(DEFAULT_X, DEFAULT_Y);
    element::Point p2(DEFAULT_X, DEFAULT_Y);
    element::Point p3(DEFAULT_X + 1, DEFAULT_Y);
    element::Point p4(DEFAULT_X, DEFAULT_Y + 1);

    ASSERT_EQ(p1, p2);
    ASSERT_NE(p1, p3);
    ASSERT_NE(p1, p4);
}

TEST_F(PointTest, addition)
{
    element::Point p1(DEFAULT_X, DEFAULT_Y);
    element::Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p1 + p2, element::Point(DEFAULT_X * 2 + 1, DEFAULT_Y * 2 + 1));
}

TEST_F(PointTest, subtraction)
{
    element::Point p1(DEFAULT_X, DEFAULT_Y);
    element::Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p2 - p1, element::Point(1, 1));
}
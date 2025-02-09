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
    Point p1(DEFAULT_X, DEFAULT_Y);
    Point p2{.x = DEFAULT_X, .y = DEFAULT_Y};
    Point p3(p1);

    ASSERT_EQ(p1, Point(DEFAULT_X, DEFAULT_Y));
    ASSERT_EQ(p2, Point(DEFAULT_X, DEFAULT_Y));
    ASSERT_EQ(p3, Point(DEFAULT_X, DEFAULT_Y));
}

TEST_F(PointTest, equality)
{
    Point p1(DEFAULT_X, DEFAULT_Y);
    Point p2(DEFAULT_X, DEFAULT_Y);
    Point p3(DEFAULT_X + 1, DEFAULT_Y);
    Point p4(DEFAULT_X, DEFAULT_Y + 1);

    ASSERT_EQ(p1, p2);
    ASSERT_NE(p1, p3);
    ASSERT_NE(p1, p4);
}

TEST_F(PointTest, addition)
{
    Point p1(DEFAULT_X, DEFAULT_Y);
    Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p1 + p2, Point(DEFAULT_X * 2 + 1, DEFAULT_Y * 2 + 1));
}

TEST_F(PointTest, subtraction)
{
    Point p1(DEFAULT_X, DEFAULT_Y);
    Point p2(DEFAULT_X + 1, DEFAULT_Y + 1);

    ASSERT_EQ(p2 - p1, Point(1, 1));
}
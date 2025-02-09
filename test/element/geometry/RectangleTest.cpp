#include "geometry/Rectangle.h"

#include <geometry/Size.h>
#include <gtest/gtest.h>

#include "geometry/Point.h"

class RectangleTest : public ::testing::Test
{
protected:
    static constexpr float X = 1.0f;
    static constexpr float Y = 2.0f;
    static constexpr float WIDTH = 3.0f;
    static constexpr float HEIGHT = 4.0f;
};

TEST_F(RectangleTest, CreateRectangle)
{
    element::Rectangle rect{X, Y, WIDTH, HEIGHT};

    ASSERT_EQ(rect.x, X);
    ASSERT_EQ(rect.y, Y);
    ASSERT_EQ(rect.width, WIDTH);
    ASSERT_EQ(rect.height, HEIGHT);
}

TEST_F(RectangleTest, Equality)
{
    element::Rectangle rect1{X, Y, WIDTH, HEIGHT};
    element::Rectangle rect2{X, Y, WIDTH, HEIGHT};

    ASSERT_EQ(rect1, rect2);
}

TEST_F(RectangleTest, GetPosition)
{
    element::Rectangle rect{X, Y, WIDTH, HEIGHT};

    ASSERT_EQ(rect.GetPosition(), element::Point(X, Y));
}

TEST_F(RectangleTest, GetSize)
{
    element::Rectangle rect{X, Y, WIDTH, HEIGHT};

    ASSERT_EQ(rect.GetSize(), element::Size(WIDTH, HEIGHT));
}
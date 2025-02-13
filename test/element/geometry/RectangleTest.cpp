#include "geometry/Rectangle.h"

#include <geometry/Size.h>
#include <gtest/gtest.h>

#include "geometry/Point.h"

class RectangleTest : public testing::Test
{
protected:
    static constexpr float X = 1.0f;
    static constexpr float Y = 2.0f;
    static constexpr float WIDTH = 3.0f;
    static constexpr float HEIGHT = 4.0f;
};

TEST_F(RectangleTest, CreateRectangle)
{
    constexpr element::Rectangle rect{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect.x, X);
    ASSERT_EQ(rect.y, Y);
    ASSERT_EQ(rect.width, WIDTH);
    ASSERT_EQ(rect.height, HEIGHT);
}

TEST_F(RectangleTest, Equality)
{
    constexpr element::Rectangle rect1{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };
    constexpr element::Rectangle rect2{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect1, rect2);
}

TEST_F(RectangleTest, GetPosition)
{
    constexpr element::Rectangle rect{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect.GetPosition(), element::Point(X, Y));
}

TEST_F(RectangleTest, GetSize)
{
    constexpr element::Rectangle rect{.x=X, .y=Y, .width=WIDTH, .height=HEIGHT};

    ASSERT_EQ(rect.GetSize(), element::Size(WIDTH, HEIGHT));
}

TEST_F(RectangleTest, SetPosition)
{
    element::Rectangle rect{.x = X, .y = Y, .width = WIDTH, .height = HEIGHT};

    rect.SetPosition(element::Point{.x = X + 1.0f, .y = Y + 1.0f});

    ASSERT_EQ(rect.GetPosition(), element::Point(X + 1.0f, Y + 1.0f));
}

TEST_F(RectangleTest, SetSize)
{
    element::Rectangle rect{.x = X, .y = Y, .width = WIDTH, .height = HEIGHT};

    rect.SetSize(element::Size{.width = WIDTH + 1.0f, .height = HEIGHT + 1.0f});

    ASSERT_EQ(rect.GetSize(), element::Size(WIDTH + 1.0f, HEIGHT + 1.0f));
}
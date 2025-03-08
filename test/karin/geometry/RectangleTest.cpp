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
    constexpr karin::Rectangle rect{
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
    constexpr karin::Rectangle rect1{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };
    constexpr karin::Rectangle rect2{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect1, rect2);
}

TEST_F(RectangleTest, GetPosition)
{
    constexpr karin::Rectangle rect{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect.GetPosition(), karin::Point(X, Y));
}

TEST_F(RectangleTest, GetSize)
{
    constexpr karin::Rectangle rect{
        .x = X,
        .y = Y,
        .width = WIDTH,
        .height = HEIGHT
    };

    ASSERT_EQ(rect.GetSize(), karin::Size(WIDTH, HEIGHT));
}

TEST_F(RectangleTest, SetPosition)
{
    karin::Rectangle rect{.x = X, .y = Y, .width = WIDTH, .height = HEIGHT};

    rect.SetPosition(karin::Point{.x = X + 1.0f, .y = Y + 1.0f});

    ASSERT_EQ(rect.GetPosition(), karin::Point(X + 1.0f, Y + 1.0f));
}

TEST_F(RectangleTest, SetSize)
{
    karin::Rectangle rect{.x = X, .y = Y, .width = WIDTH, .height = HEIGHT};

    rect.SetSize(karin::Size{.width = WIDTH + 1.0f, .height = HEIGHT + 1.0f});

    ASSERT_EQ(rect.GetSize(), karin::Size(WIDTH + 1.0f, HEIGHT + 1.0f));
}
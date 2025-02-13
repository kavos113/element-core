#include "color/Color.h"

#include <gtest/gtest.h>

TEST(ColorTest, CreateColor)
{
    const element::Color color(1.0f, 1.0f, 1.0f, 1.0f);

    ASSERT_EQ(color.r, 1.0f);
    ASSERT_EQ(color.g, 1.0f);
    ASSERT_EQ(color.b, 1.0f);
    ASSERT_EQ(color.a, 1.0f);
}

TEST(ColorTest, Equality)
{
    const element::Color color1(1.0f, 1.0f, 1.0f, 1.0f);
    const element::Color color2(1.0f, 1.0f, 1.0f, 1.0f);

    ASSERT_EQ(color1, color2);
}

TEST(ColorTest, Consts)
{
    ASSERT_EQ(
        element::Color(element::Color::Colors::White),
        element::Color(1.0f, 1.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Black),
        element::Color(0.0f, 0.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Red),
        element::Color(1.0f, 0.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Green),
        element::Color(0.0f, 1.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Blue),
        element::Color(0.0f, 0.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Yellow),
        element::Color(1.0f, 1.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Magenta),
        element::Color(1.0f, 0.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Cyan),
        element::Color(0.0f, 1.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        element::Color(element::Color::Colors::Transparent),
        element::Color(0.0f, 0.0f, 0.0f, 0.0f)
    );
}
#include "color/Color.h"

#include <gtest/gtest.h>

TEST(ColorTest, CreateColor)
{
    const karin::Color color(1.0f, 1.0f, 1.0f, 1.0f);

    ASSERT_EQ(color.r, 1.0f);
    ASSERT_EQ(color.g, 1.0f);
    ASSERT_EQ(color.b, 1.0f);
    ASSERT_EQ(color.a, 1.0f);
}

TEST(ColorTest, Equality)
{
    const karin::Color color1(1.0f, 1.0f, 1.0f, 1.0f);
    const karin::Color color2(1.0f, 1.0f, 1.0f, 1.0f);

    ASSERT_EQ(color1, color2);
}

TEST(ColorTest, Consts)
{
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::White),
        karin::Color(1.0f, 1.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Black),
        karin::Color(0.0f, 0.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Red),
        karin::Color(1.0f, 0.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Green),
        karin::Color(0.0f, 1.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Blue),
        karin::Color(0.0f, 0.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Yellow),
        karin::Color(1.0f, 1.0f, 0.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Magenta),
        karin::Color(1.0f, 0.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Cyan),
        karin::Color(0.0f, 1.0f, 1.0f, 1.0f)
    );
    ASSERT_EQ(
        karin::Color(karin::Color::Colors::Transparent),
        karin::Color(0.0f, 0.0f, 0.0f, 0.0f)
    );
}
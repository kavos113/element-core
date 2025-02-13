#include "geometry/Size.h"

#include <gtest/gtest.h>

class SizeTest : public testing::Test
{
};

TEST_F(SizeTest, CreateSize)
{
    constexpr element::Size size{.width=1.0f, .height=2.0f};

    ASSERT_EQ(size.width, 1.0f);
    ASSERT_EQ(size.height, 2.0f);
}

TEST_F(SizeTest, Equality)
{
    constexpr element::Size size1{.width=1.0f, .height=2.0f};
    constexpr element::Size size2{.width=1.0f, .height=2.0f};

    ASSERT_EQ(size1, size2);
}
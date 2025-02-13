#include "geometry/Size.h"

#include <gtest/gtest.h>

class SizeTest : public testing::Test
{
};

TEST_F(SizeTest, CreateSize)
{
    constexpr element::Size size{1.0f, 2.0f};

    ASSERT_EQ(size.width, 1.0f);
    ASSERT_EQ(size.height, 2.0f);
}

TEST_F(SizeTest, Equality)
{
    constexpr element::Size size1{1.0f, 2.0f};
    constexpr element::Size size2{1.0f, 2.0f};

    ASSERT_EQ(size1, size2);
}
#include "windows/direct2d/dwriteFactory.h"

#include <gtest/gtest.h>

TEST(dwriteFactoryTest, GetFactory)
{
    const auto factory = element::dwriteFactory::Get();
    ASSERT_NE(factory, nullptr);
}
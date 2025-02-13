#include <element/windows/direct2d/d2dFactory.h>
#include <gtest/gtest.h>
#include <windows.h>

TEST(d2dFactoryTest, GetFactory)
{
    const auto factory = element::d2dFactory::Get();
    ASSERT_NE(factory, nullptr);
}
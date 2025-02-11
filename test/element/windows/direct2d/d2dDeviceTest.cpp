#include <element/windows/direct2d/d2dDevice.h>
#include <gtest/gtest.h>

TEST(d2dDeviceTest, GetDevice)
{
    auto device = element::d2dDevice::Get();
    ASSERT_NE(device, nullptr);
}
#include <karin/windows/direct2d/d2dDevice.h>
#include <gtest/gtest.h>

TEST(d2dDeviceTest, GetDevice)
{
    const auto device = karin::d2dDevice::Get();
    ASSERT_NE(device, nullptr);
}
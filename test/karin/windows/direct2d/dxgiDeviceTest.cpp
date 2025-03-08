#include "windows/direct2d/dxgiDevice.h"

#include <gtest/gtest.h>

TEST(dxgiDeviceTest, GetDevice)
{
    const auto device = karin::dxgiDevice::Get();
    ASSERT_NE(nullptr, device);
}
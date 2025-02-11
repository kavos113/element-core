#include "windows/direct2d/dxgiDevice.h"

#include <gtest/gtest.h>

TEST(dxgiDeviceTest, GetDevice)
{
    auto device = element::dxgiDevice::Get();
    ASSERT_NE(nullptr, device);
}
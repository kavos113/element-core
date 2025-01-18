#include <element_windows.h>
#include <gtest/gtest.h>
#include <Windows.h>

class winWindowTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(winWindowTest, GenerateWindow)
{
    element::winWindow window;
    constexpr int width = 800;
    constexpr int height = 600;
    HRESULT const hr = window.Create(L"Test Window", 0, 0, width, height);

    ASSERT_EQ(hr, S_OK);
}
#include <element_windows.h>
#include <gtest/gtest.h>
#include <Windows.h>

class win_WindowTest : public ::testing::Test
{
   protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(win_WindowTest, generate_window)
{
    element::win_Window window;
    HRESULT hr = window.Create(L"Test Window", 0, 0, 800, 600);

    ASSERT_EQ(hr, S_OK);
}
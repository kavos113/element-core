#include <element_windows.h>
#include <gtest/gtest.h>
#include <Windows.h>

#include <future>
#include <print>
#include <thread>

#include "../../utils/WindowsGUITester.h"

class winWindowTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    static constexpr int width = 800;
    static constexpr int height = 600;
};

TEST_F(winWindowTest, GenerateWindow)
{
    element::winWindow window;
    HRESULT const hr = window.Create(L"Test Window", 0, 0, width, height);

    ASSERT_EQ(hr, S_OK);
    ASSERT_EQ(window.IsActive(), true);
}

TEST_F(winWindowTest, DestroyWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 2", 0, 0, width, height);
    window.Destroy();

    ASSERT_EQ(window.IsActive(), false);
}

TEST_F(winWindowTest, ShowWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 3", 0, 0, width, height);

    ASSERT_EQ(window.IsShow(), false);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        std::chrono::milliseconds(1000),
        WM_QUIT,
        0,
        0,
        [&window]() { ASSERT_EQ(window.IsShow(), true); }
    );

    auto future = tester.RunAsync();
    window.Show();
    future.get();

    ASSERT_EQ(window.IsShow(), false);
}
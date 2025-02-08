#include <element_windows.h>
#include <gtest/gtest.h>
#include <Windows.h>

#include <future>
#include <print>
#include <thread>

#include "../../utils/WindowsGUITester.h"

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

static constexpr std::chrono::duration<int, std::milli> INTERVAL
    = std::chrono::milliseconds(1000);

TEST(winWindowTest, GenerateWindow)
{
    element::winWindow window;
    HRESULT const hr = window.Create(L"Test Window", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(hr, S_OK);
    ASSERT_EQ(window.IsActive(), true);
}

TEST(winWindowTest, ShowWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 3", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.IsShow(), false);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]() { ASSERT_EQ(window.IsShow(), true); }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]() { ASSERT_EQ(window.IsShow(), false); }
    );

    auto future = tester.RunAsync();
    window.Show();
    window.Run();
    future.get();

    ASSERT_EQ(window.IsShow(), false);
}

TEST(winWindowTest, HideWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 4", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.IsShow(), false);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]() { ASSERT_EQ(window.IsShow(), true); }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Hide(); },
        [&window]() { ASSERT_EQ(window.IsShow(), false); }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]() { ASSERT_EQ(window.IsShow(), true); }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]() { ASSERT_EQ(window.IsShow(), false); }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}
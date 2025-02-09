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
    = std::chrono::milliseconds(500);

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

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::HIDE
            );
        }
    );

    auto future = tester.RunAsync();
    window.Show();
    window.Run();
    future.get();

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);
}

TEST(winWindowTest, HideWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 4", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Hide(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::HIDE
            );
            ASSERT_EQ(window.IsActive(), true);
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::HIDE
            );
        }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}

TEST(winWindowTest, MinimizeWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 5", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Minimize(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::MINIMIZE
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::HIDE
            );
        }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}

TEST(winWindowTest, MaximizeWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 6", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Show(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window]() { window.Maximize(); },
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::MAXIMIZE
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]()
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::HIDE
            );
        }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}

// TEST(winWindowTest, SetSize)
// {
//     element::winWindow window;
//     window.Create(L"Test Window 7", 0, 0, WIDTH, HEIGHT);
//
//     ASSERT_EQ(window.GetSize(), element::Rectangle{0, 0, WIDTH, HEIGHT});
//
//     WindowsGUITester tester;
//     tester.RegisterWindow(window);
//     tester.AddAction(
//         INTERVAL,
//         [&window]() { window.SetSize(400, 300); },
//         [&window]()
//         { ASSERT_EQ(window.GetSize(), element::Rectangle{0, 0, 400, 300}); }
//     );
//     tester.AddAction(
//         INTERVAL,
//         WM_CLOSE,
//         0,
//         0,
//         [&window]()
//         { ASSERT_EQ(window.GetSize(), element::Rectangle{0, 0, 400, 300}); }
//     );
//
//     auto future = tester.RunAsync();
//     window.Run();
//     future.get();
// }
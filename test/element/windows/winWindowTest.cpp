#include "windows/winWindow.h"

#include <gtest/gtest.h>
#include <Windows.h>

#include <future>
#include <print>
#include <thread>

#include "../../utils/WindowsGUITester.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Size.h"

static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;

static constexpr std::chrono::duration<int, std::milli> INTERVAL
    = std::chrono::milliseconds(200);

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
        [&window] { window.Show(); },
        [&window]
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
        [&window]
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
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window] { window.Hide(); },
        [&window]
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
        [&window] { window.Show(); },
        [&window]
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
        [&window]
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
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window] { window.Minimize(); },
        [&window]
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
        [&window]
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
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window] { window.Maximize(); },
        [&window]
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
        [&window]
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

TEST(winWindowTest, SetSize)
{
    element::winWindow window;
    window.Create(L"Test Window 7", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetSize(), element::Size(WIDTH, HEIGHT));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window] { window.SetSize({.width = 400, .height = 300}); },
        [&window] { ASSERT_EQ(window.GetSize(), element::Size(400, 300)); }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window] { ASSERT_EQ(window.GetSize(), element::Size(400, 300)); }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}

TEST(winWindowTest, SetPosition)
{
    element::winWindow window;
    window.Create(L"Test Window 8", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetPosition(), element::Point(0, 0));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window] { window.SetPosition({.x = 100, .y = 100}); },
        [&window] { ASSERT_EQ(window.GetPosition(), element::Point(100, 100)); }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window] { ASSERT_EQ(window.GetPosition(), element::Point(100, 100)); }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}

TEST(winWindowTest, SetRectangle)
{
    element::winWindow window;
    window.Create(L"Test Window 9", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetRectangle(), element::Rectangle(0, 0, WIDTH, HEIGHT));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction(
        INTERVAL,
        [&window] { window.Show(); },
        [&window]
        {
            ASSERT_EQ(
                window.GetShowStatus(),
                element::winWindow::ShowStatus::SHOW
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        [&window]
        { window.SetRectangle(element::Rectangle(100, 100, 400, 300)); },
        [&window]
        {
            ASSERT_EQ(
                window.GetRectangle(),
                element::Rectangle(100, 100, 400, 300)
            );
        }
    );
    tester.AddAction(
        INTERVAL,
        WM_CLOSE,
        0,
        0,
        [&window]
        {
            ASSERT_EQ(
                window.GetRectangle(),
                element::Rectangle(100, 100, 400, 300)
            );
        }
    );

    auto future = tester.RunAsync();
    window.Run();
    future.get();
}
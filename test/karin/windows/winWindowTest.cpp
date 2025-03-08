#include "windows/winWindow.h"

#include <gtest/gtest.h>
#include <Windows.h>

#include <future>
#include <print>
#include <thread>

#include "../../utils/WindowsGUITester.h"
#include "color/Color.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Size.h"

class winWindowTest : public testing::Test
{
protected:
    void SetUp() override
    {
#ifdef SLOW_TEST
        is_slow_test = false;
#endif
    }

    void TearDown() override
    {
    }

    static void SetUpTestSuite()
    {
        const HRESULT hr = karin::winWindow::RegisterWindowClass();
        ASSERT_HRESULT_SUCCEEDED(hr);
    }

    static void TearDownTestSuite()
    {
        const HRESULT hr = karin::winWindow::UnregisterWindowClass();
        EXPECT_HRESULT_SUCCEEDED(hr);
    }

    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    static constexpr int MOVED_X = 100;
    static constexpr int MOVED_Y = 100;

    static constexpr std::chrono::duration<int, std::milli> INTERVAL
        = std::chrono::milliseconds(200);

    bool is_slow_test = false;
};

TEST_F(winWindowTest, GenerateWindow)
{
    karin::winWindow window;
    HRESULT const hr = window.Create(L"Test Window", 0, 0, WIDTH, HEIGHT);

    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(window.IsActive(), true);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, ShowWindow)
{
    karin::winWindow window;
    window.Create(L"Test Window 3", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::SHOW);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();

    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);
}

TEST_F(winWindowTest, HideWindow)
{
    karin::winWindow window;
    window.Create(L"Test Window 4", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::SHOW);

    window.Hide();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, MinimizeWindow)
{
    karin::winWindow window;
    window.Create(L"Test Window 5", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::SHOW);

    window.Minimize();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::MINIMIZE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, MaximizeWindow)
{
    karin::winWindow window;
    window.Create(L"Test Window 6", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::SHOW);

    window.Maximize();
    ASSERT_EQ(window.GetShowStatus(), karin::winWindow::ShowStatus::MAXIMIZE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, SetSize)
{
    karin::winWindow window;
    window.Create(L"Test Window 7", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetSize(), karin::Size(WIDTH, HEIGHT));

    constexpr karin::Size changed_size(WIDTH * 2, HEIGHT * 2);

    window.SetSize(changed_size);
    ASSERT_EQ(window.GetSize(), karin::Size(WIDTH * 2, HEIGHT * 2));

    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, SetPosition)
{
    karin::winWindow window;
    window.Create(L"Test Window 8", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetPosition(), karin::Point(0, 0));

    constexpr karin::Point changed_position(MOVED_X, MOVED_Y);

    window.SetPosition(changed_position);
    ASSERT_EQ(window.GetPosition(), karin::Point(MOVED_X, MOVED_Y));

    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, SetRectangle)
{
    karin::winWindow window;
    window.Create(L"Test Window 9", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetRectangle(), karin::Rectangle(0, 0, WIDTH, HEIGHT));

    constexpr karin::Rectangle
        changed_rect(MOVED_X, MOVED_Y, WIDTH * 2, HEIGHT * 2);

    window.SetRectangle(changed_rect);
    ASSERT_EQ(
        window.GetRectangle(),
        karin::Rectangle(MOVED_X, MOVED_Y, WIDTH * 2, HEIGHT * 2)
    );

    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, SetBackgroundColor)
{
    karin::winWindow window;
    window.Create(L"Test Window 10", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(
        window.GetBackgroundColor(),
        karin::Color(1.0f, 1.0f, 1.0f, 1.0f)
    );

    const karin::Color changed_color(1.0f, 0.0f, 0.0f, 1.0f);

    window.SetBackgroundColor(changed_color);
    ASSERT_EQ(window.GetBackgroundColor(), changed_color);

    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}
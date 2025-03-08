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
        const HRESULT hr = element::winWindow::RegisterWindowClass();
        ASSERT_HRESULT_SUCCEEDED(hr);
    }

    static void TearDownTestSuite()
    {
        const HRESULT hr = element::winWindow::UnregisterWindowClass();
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
    element::winWindow window;
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
    element::winWindow window;
    window.Create(L"Test Window 3", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::SHOW);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);
}

TEST_F(winWindowTest, HideWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 4", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::SHOW);

    window.Hide();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, MinimizeWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 5", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::SHOW);

    window.Minimize();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::MINIMIZE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, MaximizeWindow)
{
    element::winWindow window;
    window.Create(L"Test Window 6", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::SHOW);

    window.Maximize();
    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::MAXIMIZE);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}

TEST_F(winWindowTest, SetSize)
{
    element::winWindow window;
    window.Create(L"Test Window 7", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetSize(), element::Size(WIDTH, HEIGHT));

    constexpr element::Size changed_size(WIDTH * 2, HEIGHT * 2);

    window.SetSize(changed_size);
    ASSERT_EQ(window.GetSize(), element::Size(WIDTH * 2, HEIGHT * 2));

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
    element::winWindow window;
    window.Create(L"Test Window 8", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetPosition(), element::Point(0, 0));

    constexpr element::Point changed_position(MOVED_X, MOVED_Y);

    window.SetPosition(changed_position);
    ASSERT_EQ(window.GetPosition(), element::Point(MOVED_X, MOVED_Y));

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
    element::winWindow window;
    window.Create(L"Test Window 9", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(window.GetRectangle(), element::Rectangle(0, 0, WIDTH, HEIGHT));

    constexpr element::Rectangle
        changed_rect(MOVED_X, MOVED_Y, WIDTH * 2, HEIGHT * 2);

    window.SetRectangle(changed_rect);
    ASSERT_EQ(
        window.GetRectangle(),
        element::Rectangle(MOVED_X, MOVED_Y, WIDTH * 2, HEIGHT * 2)
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
    element::winWindow window;
    window.Create(L"Test Window 10", 0, 0, WIDTH, HEIGHT);

    ASSERT_EQ(
        window.GetBackgroundColor(),
        element::Color(1.0f, 1.0f, 1.0f, 1.0f)
    );

    const element::Color changed_color(1.0f, 0.0f, 0.0f, 1.0f);

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
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
        is_slow_test = true;
#endif
    }

    void TearDown() override
    {
    }

    static void SetUpTestCase()
    {
        const HRESULT hr = element::winWindow::RegisterWindowClass();
        ASSERT_HRESULT_SUCCEEDED(hr);
    }

    static void TearDownTestCase()
    {
        const HRESULT hr = element::winWindow::UnregisterWindowClass();
        EXPECT_HRESULT_SUCCEEDED(hr);
    }

    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

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

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
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

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::HIDE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::HIDE
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
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

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::MINIMIZE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::MINIMIZE
    );
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

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::MAXIMIZE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::MAXIMIZE
    );
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

    element::Size changed_size(400, 300);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Size>(
        element::winWindow::WindowAction::SIZE,
        reinterpret_cast<LPARAM>(&changed_size),
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SIZE,
        element::Size(400, 300)
    );
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

    element::Point changed_position(100, 100);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Point>(
        element::winWindow::WindowAction::POSITION,
        reinterpret_cast<LPARAM>(&changed_position),
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::POSITION,
        element::Point(100, 100)
    );
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

    element::Rectangle changed_rect(100, 100, 400, 300);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Rectangle>(
        element::winWindow::WindowAction::RECTANGLE,
        reinterpret_cast<LPARAM>(&changed_rect),
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::RECTANGLE,
        element::Rectangle(100, 100, 400, 300)
    );
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

    element::Color changed_color(1.0f, 0.0f, 0.0f, 1.0f);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Color>(
        element::winWindow::WindowAction::BACKGROUND_COLOR,
        reinterpret_cast<LPARAM>(&changed_color),
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::BACKGROUND_COLOR,
        element::Color(1.0f, 0.0f, 0.0f, 1.0f)
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}
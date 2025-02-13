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

class winWindowTest : public ::testing::Test
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
        HRESULT hr = element::winWindow::RegisterWindowClass();
        ASSERT_HRESULT_SUCCEEDED(hr);
    }

    static void TearDownTestCase()
    {
        HRESULT hr = element::winWindow::UnregisterWindowClass();
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        EL_WINDOW_HIDE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::HIDE
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        EL_WINDOW_MINIMIZE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::winWindow::ShowStatus>(
        EL_WINDOW_MAXIMIZE,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Size>(
        EL_WINDOW_SIZE,
        reinterpret_cast<LPARAM>(&changed_size),
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SIZE,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Point>(
        EL_WINDOW_POSITION,
        reinterpret_cast<LPARAM>(&changed_position),
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_POSITION,
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
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Rectangle>(
        EL_WINDOW_RECTANGLE,
        reinterpret_cast<LPARAM>(&changed_rect),
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_RECTANGLE,
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

    element::Color changed_color(0.0f, 0.0f, 0.0f, 1.0f);

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        EL_WINDOW_SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction<element::Color>(
        EL_WINDOW_BACKGROUND_COLOR,
        reinterpret_cast<LPARAM>(&changed_color),
        WindowsGUITester::Assertions::EQUAL,
        EL_WINDOW_BACKGROUND_COLOR,
        element::Color(0.0f, 0.0f, 0.0f, 1.0f)
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, is_slow_test);
    window.Run();
    thread.join();
}
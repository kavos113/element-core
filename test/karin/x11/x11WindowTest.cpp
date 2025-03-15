#include "x11/x11Window.h"

#undef None
#undef Bool
#include <gtest/gtest.h>

#include "../../utils/X11GUITester.h"
#include "color/Color.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Size.h"

class x11WindowTest : public testing::Test
{
protected:
};

TEST_F(x11WindowTest, GenerateWindow)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 1", 0, 0, 800, 600);
    ASSERT_TRUE(ret);

    ASSERT_EQ(window.IsActive(), true);
}

TEST_F(x11WindowTest, ShowWindow)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 2", 0, 0, 800, 600);
    ASSERT_TRUE(ret);
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::SHOW);

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();

    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);
}

TEST_F(x11WindowTest, HideWindow)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 3", 0, 0, 800, 600);
    ASSERT_TRUE(ret);
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::SHOW);

    window.Hide();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, MaximizeWindow)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 4", 0, 0, 800, 600);
    ASSERT_TRUE(ret);
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::SHOW);

    window.Maximize();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::MAXIMIZE);

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, MinimizeWindow)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 5", 0, 0, 800, 600);
    ASSERT_TRUE(ret);
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::HIDE);

    window.Show();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::SHOW);

    window.Minimize();
    ASSERT_EQ(window.GetShowStatus(), karin::x11Window::ShowStatus::MINIMIZE);

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, SetSize)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 6", 0, 0, 800, 600);
    ASSERT_TRUE(ret);

    ASSERT_EQ(window.GetSize(), karin::Size(800, 600));

    constexpr karin::Size changed_size(1600, 1200);

    window.SetSize(changed_size);
    ASSERT_EQ(window.GetSize(), karin::Size(1600, 1200));

    window.Show();

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, SetPosition)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 7", 0, 0, 800, 600);
    ASSERT_TRUE(ret);

    ASSERT_EQ(window.GetPosition(), karin::Point(0, 0));

    constexpr karin::Point changed_position(100, 100);

    window.SetPosition(changed_position);
    ASSERT_EQ(window.GetPosition(), karin::Point(100, 100));

    window.Show();

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, SetRectangle)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 8", 0, 0, 800, 600);
    ASSERT_TRUE(ret);

    ASSERT_EQ(window.GetRectangle(), karin::Rectangle(0, 0, 800, 600));

    constexpr karin::Rectangle changed_rect(100, 100, 1600, 1200);

    window.SetRectangle(changed_rect);
    ASSERT_EQ(window.GetRectangle(), karin::Rectangle(100, 100, 1600, 1200));

    window.Show();

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}

TEST_F(x11WindowTest, SetBackgroundColor)
{
    karin::x11Window window;
    const bool ret = window.Create("Test 9", 0, 0, 800, 600);
    ASSERT_TRUE(ret);

    ASSERT_EQ(
        window.GetBackgroundColor(),
        karin::Color(1.0f, 1.0f, 1.0f, 1.0f)
    );

    const karin::Color changed_color(1.0f, 0.0f, 0.0f, 1.0f);

    window.SetBackgroundColor(changed_color);
    ASSERT_EQ(window.GetBackgroundColor(), changed_color);

    window.Show();

    X11GUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&X11GUITester::Run, &tester, false);
    window.Run();
    thread.join();
}
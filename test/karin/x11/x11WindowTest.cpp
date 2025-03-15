#include "x11/x11Window.h"

#undef None
#undef Bool
#include <gtest/gtest.h>

#include "../../utils/X11GUITester.h"

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
#include "windows/winText.h"

#include <gtest/gtest.h>

#include "../../utils/WindowsGUITester.h"
#include "windows/winWindow.h"

class winTextTest : public testing::Test
{
protected:
    void SetUp() override
    {
#ifdef SLOW_TEST
        m_isSlowTest = true;
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

    bool m_isSlowTest = false;

    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 100;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;

    static constexpr float CHANGED_FONT_SIZE = 72.0f;
};

TEST_F(winTextTest, GenerateText)
{
    element::winText text;
    HRESULT hr = text.Create(L"Test Text", 0, 0, WIDTH, HEIGHT);

    ASSERT_HRESULT_SUCCEEDED(hr);
}

TEST_F(winTextTest, ShowText)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(L"Test Text", 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    window.Add(std::move(text));

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

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();

    ASSERT_EQ(window.GetShowStatus(), element::winWindow::ShowStatus::HIDE);
}

TEST_F(winTextTest, SetText)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(L"Test Text", 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winText* text_ptr = text.get();
    window.Add(std::move(text));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetText(L"Some New Text Here ...");
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetText(), L"Some New Text Here ..."); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetPosition)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(L"Test Text", 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winText* text_ptr = text.get();
    window.Add(std::move(text));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction(
        [&text_ptr] { text_ptr->SetPosition(element::Point(100, 100)); },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetPosition(), element::Point(100, 100)); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetSize)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(
        L"Very very very long text, Very very very long text, Very very very "
        L"long text, Very very very long text, Very very very long text.",
        0,
        0,
        WIDTH,
        HEIGHT
    );
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winText* text_ptr = text.get();
    window.Add(std::move(text));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr
                = text_ptr->SetSize(element::Size(WIDTH * 2, HEIGHT * 2));
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetSize(),
                element::Size(WIDTH * 2, HEIGHT * 2)
            );
        }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetRectangle)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(
        L"Very very very long text, Very very very long text, Very very very "
        L"long text, Very very very long text, Very very very long text.",
        0,
        0,
        WIDTH,
        HEIGHT
    );
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winText* text_ptr = text.get();
    window.Add(std::move(text));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetRectangle(
                element::Rectangle(100, 100, WIDTH * 2, HEIGHT * 2)
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetRectangle(),
                element::Rectangle(100, 100, WIDTH * 2, HEIGHT * 2)
            );
        }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontSize)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(L"Text Test", 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winText* text_ptr = text.get();
    window.Add(std::move(text));

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.AddAction<element::winWindow::ShowStatus>(
        element::winWindow::WindowAction::SHOW,
        0,
        WindowsGUITester::Assertions::EQUAL,
        element::winWindow::WindowAction::SHOWSTATUS,
        element::winWindow::ShowStatus::SHOW
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontSize(CHANGED_FONT_SIZE);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr] { ASSERT_EQ(text_ptr->GetFontSize(), CHANGED_FONT_SIZE); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}
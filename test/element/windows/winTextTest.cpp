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

    const std::wstring TEXT = L"Test Text";
    const std::wstring NEW_TEXT = L"Some New Text Here ...";
    const std::wstring LONG_TEXT
        = L"Very very very long text, Very very very long text, Very very very "
          L"long text, Very very very long text, Very very very long text.";
    const std::wstring PARAGRAPH_TEXT
        = L"This is a paragraph text. I am testing the paragraph text. This is "
          L"the third sentence of the paragraph text.";
};

TEST_F(winTextTest, GenerateText)
{
    element::winText text;
    HRESULT hr = text.Create(TEXT, 0, 0, WIDTH, HEIGHT);

    ASSERT_HRESULT_SUCCEEDED(hr);
}

TEST_F(winTextTest, ShowText)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
        [&text_ptr, this]
        {
            HRESULT hr = text_ptr->SetText(NEW_TEXT);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr, this] { ASSERT_EQ(text_ptr->GetText(), NEW_TEXT); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetPosition)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
    HRESULT hr = text->Create(LONG_TEXT, 0, 0, WIDTH, HEIGHT);
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
    HRESULT hr = text->Create(LONG_TEXT, 0, 0, WIDTH, HEIGHT);
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
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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

TEST_F(winTextTest, SetHorizontalAlignment)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetHorizontalAlignment(
                element::Font::HorizontalAlignment::JUSTIFIED
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetHorizontalAlignment(),
                element::Font::HorizontalAlignment::JUSTIFIED
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetHorizontalAlignment(
                element::Font::HorizontalAlignment::CENTER
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetHorizontalAlignment(),
                element::Font::HorizontalAlignment::CENTER
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetHorizontalAlignment(
                element::Font::HorizontalAlignment::LEADING
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetHorizontalAlignment(),
                element::Font::HorizontalAlignment::LEADING
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetHorizontalAlignment(
                element::Font::HorizontalAlignment::TRAILING
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetHorizontalAlignment(),
                element::Font::HorizontalAlignment::TRAILING
            );
        }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetVerticalAlignment)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetVerticalAlignment(
                element::Font::VerticalAlignment::BOTTOM
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetVerticalAlignment(),
                element::Font::VerticalAlignment::BOTTOM
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetVerticalAlignment(
                element::Font::VerticalAlignment::CENTER
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetVerticalAlignment(),
                element::Font::VerticalAlignment::CENTER
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetVerticalAlignment(
                element::Font::VerticalAlignment::TOP
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetVerticalAlignment(),
                element::Font::VerticalAlignment::TOP
            );
        }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontFamily)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetFontFamily(L"Times New Roman");
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontFamily(), L"Times New Roman"); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontFamily(L"Courier New");
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr] { ASSERT_EQ(text_ptr->GetFontFamily(), L"Courier New"); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStyle)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetFontFamily(L"Times New Roman");
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontFamily(), L"Times New Roman"); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontStyle(element::Font::Style::ITALIC);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontStyle(), element::Font::Style::ITALIC); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontStyle(element::Font::Style::NORMAL);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontStyle(), element::Font::Style::NORMAL); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontStyle(element::Font::Style::OBLIQUE);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontStyle(), element::Font::Style::OBLIQUE); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStretch)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetFontStretch(
                element::Font::Stretch::ULTRA_CONDENSED
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetFontStretch(),
                element::Font::Stretch::ULTRA_CONDENSED
            );
        }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontStretch(
                element::Font::Stretch::ULTRA_EXPANDED
            );
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        {
            ASSERT_EQ(
                text_ptr->GetFontStretch(),
                element::Font::Stretch::ULTRA_EXPANDED
            );
        }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontWeight)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetFontWeight(element::Font::Weight::THIN);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontWeight(), element::Font::Weight::THIN); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontWeight(909);
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetFontWeight(), element::Font::Weight::BLACK); }
    );
    tester.AddAction(
        [&text_ptr]
        {
            HRESULT hr = text_ptr->SetFontWeight(2000);
            ASSERT_HRESULT_FAILED(hr);
        },
        [] {}
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontColor)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
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
            HRESULT hr = text_ptr->SetColor(element::Color(1.0f, 0, 0));
            ASSERT_HRESULT_SUCCEEDED(hr);
        },
        [&text_ptr]
        { ASSERT_EQ(text_ptr->GetColor(), element::Color(1.0f, 0, 0)); }
    );
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}
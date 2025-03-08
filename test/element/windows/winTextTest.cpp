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

    static constexpr int CHANGED_X = 100;
    static constexpr int CHANGED_Y = 100;

    static constexpr float CHANGED_FONT_SIZE = 72.0f;

    const std::wstring TEXT = L"Test Text";
    const std::wstring NEW_TEXT = L"Some New Text Here ...";
    const std::wstring LONG_TEXT
        = L"Very very very long text, Very very very long text, Very very very "
          L"long text, Very very very long text, Very very very long text.";
    const std::wstring PARAGRAPH_TEXT
        = L"This is a paragraph text. I am testing the paragraph text. \nThis "
          L"is "
          L"the third sentence of the paragraph text.";
};

TEST_F(winTextTest, GenerateText)
{
    element::winText text;
    const HRESULT hr = text.Create(TEXT, 0, 0, WIDTH, HEIGHT);

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

    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    hr = text->SetText(NEW_TEXT);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetText(), NEW_TEXT);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    text->SetPosition(element::Point(CHANGED_X, CHANGED_Y));
    ASSERT_EQ(text->GetPosition(), element::Point(CHANGED_X, CHANGED_Y));

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    hr = text->SetSize(element::Size(WIDTH * 2, HEIGHT * 2));
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetSize(), element::Size(WIDTH * 2, HEIGHT * 2));

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    hr = text->SetRectangle(
        element::Rectangle(CHANGED_X, CHANGED_Y, WIDTH * 2, HEIGHT * 2)
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetRectangle(),
        element::Rectangle(CHANGED_X, CHANGED_Y, WIDTH * 2, HEIGHT * 2)
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    hr = text->SetFontSize(CHANGED_FONT_SIZE);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontSize(), CHANGED_FONT_SIZE);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetHorizontalAlignmentLeading)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetHorizontalAlignment(
        element::Paragraph::HorizontalAlignment::LEADING
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetHorizontalAlignment(),
        element::Paragraph::HorizontalAlignment::LEADING
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetHorizontalAlignmentTrailing)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetHorizontalAlignment(
        element::Paragraph::HorizontalAlignment::TRAILING
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetHorizontalAlignment(),
        element::Paragraph::HorizontalAlignment::TRAILING
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetHorizontalAlignmentCenter)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetHorizontalAlignment(
        element::Paragraph::HorizontalAlignment::CENTER
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetHorizontalAlignment(),
        element::Paragraph::HorizontalAlignment::CENTER
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetHorizontalAlignmentJustified)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetHorizontalAlignment(
        element::Paragraph::HorizontalAlignment::JUSTIFIED
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetHorizontalAlignment(),
        element::Paragraph::HorizontalAlignment::JUSTIFIED
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetVerticalAlignmentBottom)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetVerticalAlignment(
        element::Paragraph::VerticalAlignment::BOTTOM
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetVerticalAlignment(),
        element::Paragraph::VerticalAlignment::BOTTOM
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetVerticalAlignmentTop)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetVerticalAlignment(element::Paragraph::VerticalAlignment::TOP);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetVerticalAlignment(),
        element::Paragraph::VerticalAlignment::TOP
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetVerticalAlignmentCenter)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetVerticalAlignment(
        element::Paragraph::VerticalAlignment::CENTER
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetVerticalAlignment(),
        element::Paragraph::VerticalAlignment::CENTER
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
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

    hr = text->SetFontFamily(L"Times New Roman");
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontFamily(), L"Times New Roman");

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStyleItalic)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    text->SetFontFamily(L"Times New Roman");
    hr = text->SetFontStyle(element::Font::Style::ITALIC);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontStyle(), element::Font::Style::ITALIC);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStyleNormal)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    text->SetFontFamily(L"Times New Roman");
    hr = text->SetFontStyle(element::Font::Style::NORMAL);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontStyle(), element::Font::Style::NORMAL);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStyleOblique)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    text->SetFontFamily(L"Times New Roman");
    hr = text->SetFontStyle(element::Font::Style::OBLIQUE);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontStyle(), element::Font::Style::OBLIQUE);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStretchUltracondensed)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    text->SetFontFamily(L"Times New Roman");
    hr = text->SetFontStretch(element::Font::Stretch::ULTRA_CONDENSED);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontStretch(), element::Font::Stretch::ULTRA_CONDENSED);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontStretchUltraexpanded)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    text->SetFontFamily(L"Times New Roman");
    hr = text->SetFontStretch(element::Font::Stretch::ULTRA_EXPANDED);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontStretch(), element::Font::Stretch::ULTRA_EXPANDED);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontWeightThin)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetFontWeight(element::Font::Weight::THIN);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontWeight(), element::Font::Weight::THIN);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontWeightCalculatedBlack)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    constexpr int black_weight = 909;
    hr = text->SetFontWeight(black_weight);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetFontWeight(), element::Font::Weight::BLACK);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetFontWeightFailedInvalidWeight)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    constexpr uint16_t invalid_weight = 10000;
    hr = text->SetFontWeight(invalid_weight);
    ASSERT_HRESULT_FAILED(hr);
}

TEST_F(winTextTest, SetFontColor)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetColor(element::Color(1.0f, 0.0f, 0.0f, 1.0f));
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetColor(), element::Color(1.0f, 0.0f, 0.0f, 1.0f));

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetLineHeight)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    constexpr float changed_line_height = 2.0f;

    hr = text->SetLineHeight(changed_line_height);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetLineHeight(), changed_line_height);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetTrimmingWord)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetTrimming(element::Paragraph::Trimming::WORD);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetTrimming(), element::Paragraph::Trimming::WORD);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetTrimmingCharacter)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetTrimming(element::Paragraph::Trimming::CHARACTER);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetTrimming(), element::Paragraph::Trimming::CHARACTER);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetTrimmingNone)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetTrimming(element::Paragraph::Trimming::NONE);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetTrimming(), element::Paragraph::Trimming::NONE);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetWordWrappingWord)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetWordWrapping(element::Paragraph::Wrapping::WORD);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetWordWrapping(), element::Paragraph::Wrapping::WORD);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetWordWrappingCharacter)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetWordWrapping(element::Paragraph::Wrapping::CHARACTER);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetWordWrapping(), element::Paragraph::Wrapping::CHARACTER);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetWordWrappingNone)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetWordWrapping(element::Paragraph::Wrapping::NONE);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(text->GetWordWrapping(), element::Paragraph::Wrapping::NONE);

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetDirectionTopToBottom)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetDirection(
        element::Paragraph::Direction::TOP_TO_BOTTOM,
        element::Paragraph::Direction::LEFT_TO_RIGHT
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetFlowDirection(),
        element::Paragraph::Direction::TOP_TO_BOTTOM
    );
    ASSERT_EQ(
        text->GetReadingDirection(),
        element::Paragraph::Direction::LEFT_TO_RIGHT
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetDirectionBottomToTop)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetDirection(
        element::Paragraph::Direction::BOTTOM_TO_TOP,
        element::Paragraph::Direction::RIGHT_TO_LEFT
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetFlowDirection(),
        element::Paragraph::Direction::BOTTOM_TO_TOP
    );
    ASSERT_EQ(
        text->GetReadingDirection(),
        element::Paragraph::Direction::RIGHT_TO_LEFT
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetDirectionRightToLeft)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetDirection(
        element::Paragraph::Direction::RIGHT_TO_LEFT,
        element::Paragraph::Direction::TOP_TO_BOTTOM
    );
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_EQ(
        text->GetFlowDirection(),
        element::Paragraph::Direction::RIGHT_TO_LEFT
    );
    ASSERT_EQ(
        text->GetReadingDirection(),
        element::Paragraph::Direction::TOP_TO_BOTTOM
    );

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetDirectionFailedInvalidDirection)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(PARAGRAPH_TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetDirection(
        element::Paragraph::Direction::RIGHT_TO_LEFT,
        element::Paragraph::Direction::LEFT_TO_RIGHT
    );
    ASSERT_HRESULT_FAILED(hr);

    hr = text->SetDirection(
        element::Paragraph::Direction::TOP_TO_BOTTOM,
        element::Paragraph::Direction::TOP_TO_BOTTOM
    );
    ASSERT_HRESULT_FAILED(hr);
}

TEST_F(winTextTest, SetUnderline)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetUnderline(true);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_TRUE(text->IsUnderlined());

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}

TEST_F(winTextTest, SetLineThrough)
{
    auto text = std::make_unique<element::winText>();
    HRESULT hr = text->Create(TEXT, 0, 0, WIDTH, HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    element::winWindow window;
    hr = window.Create(L"Test Window", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    ASSERT_HRESULT_SUCCEEDED(hr);

    hr = text->SetLineThrough(true);
    ASSERT_HRESULT_SUCCEEDED(hr);
    ASSERT_TRUE(text->IsLineThrough());

    window.Add(std::move(text));
    window.Show();

    WindowsGUITester tester;
    tester.RegisterWindow(window);
    tester.CloseWindow();

    std::thread thread(&WindowsGUITester::Run, &tester, m_isSlowTest);
    window.Run();
    thread.join();
}
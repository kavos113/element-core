#include "windows/winText.h"

#include <gtest/gtest.h>

#include "windows/winWindow.h"

class winTextTest : public testing::Test
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

    bool is_slow_test = false;

    static constexpr int WIDTH = 200;
    static constexpr int HEIGHT = 100;
};

TEST_F(winTextTest, GenerateText)
{
    element::winText text;
    HRESULT hr = text.Create(L"Test Text", 0, 0, WIDTH, HEIGHT);

    ASSERT_HRESULT_SUCCEEDED(hr);
}

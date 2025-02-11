#include "windows/direct2d/d2dWindow.h"

#include <gtest/gtest.h>
#include <Windows.h>

class d2dWindowTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        WNDCLASSEX wcex = {};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.lpfnWndProc = DefWindowProc;
        wcex.hInstance = GetModuleHandle(nullptr);
        wcex.lpszClassName = "test";
        RegisterClassEx(&wcex);

        hwnd = CreateWindow(
            "test",
            "test",
            WS_OVERLAPPEDWINDOW,
            0,
            0,
            640,
            480,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );
    }

    HWND hwnd = nullptr;
};

TEST_F(d2dWindowTest, CreateD2DWindow)
{
    element::d2dWindow window;
    HRESULT hr = window.Create(hwnd);

    ASSERT_NE(nullptr, window.GetDeviceContext());
    ASSERT_EQ(hr, S_OK);
}

TEST_F(d2dWindowTest, DrawD2DWindow)
{
    element::d2dWindow window;
    HRESULT hr = window.Create(hwnd);

    ASSERT_EQ(hr, S_OK);

    window.BeginDraw();
    hr = window.EndDraw();

    ASSERT_EQ(hr, S_OK);
}
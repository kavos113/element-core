#include "windows/direct2d/d2dWindow.h"

#include <gtest/gtest.h>
#include <Windows.h>

TEST(d2dWindowTest, CreateD2DWindow)
{
    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.lpfnWndProc = DefWindowProc;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpszClassName = "test";
    RegisterClassEx(&wcex);

    HWND hwnd = CreateWindow(
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

    element::d2dWindow window;
    window.Create(hwnd);
    ASSERT_NE(nullptr, window.GetDeviceContext());
}
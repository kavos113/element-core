#include "windows/winWindow.h"

namespace element
{
HRESULT winWindow::Create(
    const wchar_t *title,
    int x,
    int y,
    int width,
    int height
)
{
    WNDCLASSEX const wc
        = {.cbSize = sizeof(WNDCLASSEX),
           .style = CS_HREDRAW | CS_VREDRAW,
           .lpfnWndProc = DefWindowProc,
           .cbClsExtra = 0,
           .cbWndExtra = 0,
           .hInstance = GetModuleHandle(nullptr),
           .hIcon = LoadIcon(nullptr, IDI_APPLICATION),
           .hCursor = LoadCursor(nullptr, IDC_ARROW),
           .hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
           .lpszMenuName = nullptr,
           .lpszClassName = title,
           .hIconSm = LoadIcon(nullptr, IDI_APPLICATION)};


    ATOM const res = RegisterClassEx(&wc);
    if (res == 0)
    {
        return E_FAIL;
    }

    m_hwnd = CreateWindowEx(
        0,
        title,
        title,
        WS_OVERLAPPEDWINDOW,
        x,
        y,
        width,
        height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );
    if (m_hwnd == nullptr)
    {
        return E_FAIL;
    }

    return S_OK;
}
}  // namespace element

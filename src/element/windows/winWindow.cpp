#include "windows/winWindow.h"

namespace element
{
winWindow::~winWindow()
{
    Destroy();
}

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

bool winWindow::IsActive() const
{
    return m_hwnd != nullptr;
}

bool winWindow::IsShow() const
{
    return m_isShow;
}

HWND winWindow::GetHwnd() const
{
    return m_hwnd;
}

void winWindow::Destroy()
{
    if (m_hwnd != nullptr)
    {
        PostQuitMessage(0);
        DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
    }
}

void winWindow::Show()
{
    if (m_hwnd != nullptr)
    {
        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);
        m_isShow = true;
    }

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    m_isShow = false;
}

}  // namespace element

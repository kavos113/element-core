#include "windows/winWindow.h"

#include <iostream>

namespace element
{
winWindow::~winWindow() = default;

HRESULT winWindow::Create(
    const wchar_t *title, int x, int y, int width, int height
)
{
    WNDCLASSEX const wc
        = {.cbSize = sizeof(WNDCLASSEX),
           .style = CS_HREDRAW | CS_VREDRAW,
           .lpfnWndProc = WinWindowProc,
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
        this
    );
    if (m_hwnd == nullptr)
    {
        return E_FAIL;
    }

    m_rect = Rectangle(x, y, width, height);

    HRESULT hr = m_d2dWindow.Create(m_hwnd);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Direct2D window" << std::endl;
        return hr;
    }

    return S_OK;
}

LRESULT winWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
            DestroyWindow(m_hwnd);
            return 0;

        case WM_PAINT:
            m_d2dWindow.BeginDraw();
            m_d2dWindow.EndDraw();
            return 0;

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
}

bool winWindow::IsActive() const
{
    return m_hwnd != nullptr;
}

winWindow::ShowStatus winWindow::GetShowStatus() const
{
    return m_showStatus;
}

HWND winWindow::GetHwnd() const
{
    return m_hwnd;
}

void winWindow::Show()
{
    if (m_hwnd != nullptr)
    {
        ShowWindow(m_hwnd, SW_SHOW);
        UpdateWindow(m_hwnd);
        m_showStatus = ShowStatus::SHOW;
    }
}

void winWindow::Run()
{
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(m_hwnd);
    m_hwnd = nullptr;

    m_showStatus = ShowStatus::HIDE;
}

void winWindow::Hide()
{
    if (m_hwnd != nullptr)
    {
        ShowWindow(m_hwnd, SW_HIDE);
        m_showStatus = ShowStatus::HIDE;
    }
}

void winWindow::Minimize()
{
    if (m_hwnd != nullptr)
    {
        ShowWindow(m_hwnd, SW_MINIMIZE);
        m_showStatus = ShowStatus::MINIMIZE;
    }
}

void winWindow::Maximize()
{
    if (m_hwnd != nullptr)
    {
        ShowWindow(m_hwnd, SW_MAXIMIZE);
        m_showStatus = ShowStatus::MAXIMIZE;
    }
}

Size winWindow::GetSize() const
{
    return m_rect.GetSize();
}

void winWindow::SetSize(Size size)
{
    SetWindowPos(
        m_hwnd,
        HWND_TOP,
        0,
        0,
        static_cast<int>(size.width),
        static_cast<int>(size.height),
        SWP_NOMOVE
    );
    m_rect.SetSize(size);
}

Point winWindow::GetPosition() const
{
    return m_rect.GetPosition();
}

void winWindow::SetPosition(Point position)
{
    SetWindowPos(
        m_hwnd,
        HWND_TOP,
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        0,
        0,
        SWP_NOSIZE
    );
    m_rect.SetPosition(position);
}

Rectangle winWindow::GetRectangle() const
{
    return m_rect;
}

void winWindow::SetRectangle(Rectangle rect)
{
    SetWindowPos(
        m_hwnd,
        HWND_TOP,
        static_cast<int>(rect.x),
        static_cast<int>(rect.y),
        static_cast<int>(rect.width),
        static_cast<int>(rect.height),
        0
    );
    m_rect = rect;
}

Color winWindow::GetBackgroundColor() const
{
    return m_backgroundColor;
}

void winWindow::SetBackgroundColor(Color color)
{
    m_backgroundColor = color;
    D2D1_COLOR_F d2dC_color = D2D1::ColorF(color.r, color.g, color.b, color.a);
    m_d2dWindow.SetClearColor(d2dC_color);

    InvalidateRect(m_hwnd, nullptr, false);
}

}  // namespace element

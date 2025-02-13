#include "windows/winWindow.h"

#include <iostream>

namespace element
{

winWindow::~winWindow() = default;

HRESULT winWindow::RegisterWindowClass()
{
    WNDCLASSEX const wc = {
        .cbSize = sizeof(WNDCLASSEX),
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = WinWindowProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = GetModuleHandle(nullptr),
        .hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1),
        .lpszMenuName = nullptr,
        .lpszClassName = class_name,
    };

    if (ATOM const res = RegisterClassEx(&wc); res == 0)
    {
        std::cout << "Failed to register window class" << std::endl;
        return E_FAIL;
    }

    return S_OK;
}

HRESULT winWindow::UnregisterWindowClass()
{
    if (const BOOL res = UnregisterClass(class_name, GetModuleHandle(nullptr));
        res == 0)
    {
        std::cout << "Failed to unregister window class" << std::endl;
        return E_FAIL;
    }

    return S_OK;
}

HRESULT winWindow::Create(
    const wchar_t *title,
    const int x,
    const int y,
    const int width,
    const int height
)
{
    m_hwnd = CreateWindowEx(
        0,
        class_name,
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
        std::cout << "Failed to create window" << std::endl;
        return E_FAIL;
    }

    m_rect = Rectangle(
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(width),
        static_cast<float>(height)
    );

    if (const HRESULT hr = m_d2dWindow.Create(m_hwnd); FAILED(hr))
    {
        std::cout << "Failed to create Direct2D window" << std::endl;
        return hr;
    }

    return S_OK;
}

LRESULT winWindow::WinWindowProc(
    HWND hwnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam
)
{
    winWindow *pThis = nullptr;

    if (uMsg == WM_CREATE)
    {
        const auto *pCreate = reinterpret_cast<CREATESTRUCT *>(lParam);
        pThis = reinterpret_cast<winWindow *>(pCreate->lpCreateParams);
        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pThis)
        );

        pThis->m_hwnd = hwnd;
    }
    else
    {
        pThis = reinterpret_cast<winWindow *>(
            GetWindowLongPtr(hwnd, GWLP_USERDATA)
        );
    }

    if (pThis != nullptr)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT winWindow::HandleMessage(
    const UINT uMsg, const WPARAM wParam, const LPARAM lParam
)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
        {
            if (const BOOL res = DestroyWindow(m_hwnd); res == 0)
            {
                std::cout << "Failed to destroy window" << std::endl;
                return -1;
            }
            m_hwnd = nullptr;
            return 0;
        }

        case WM_PAINT:
        {
            m_d2dWindow.BeginDraw();
            if (const HRESULT hr = m_d2dWindow.EndDraw(); FAILED(hr))
            {
                std::cout << "Failed to end draw" << std::endl;
                DestroyWindow(m_hwnd);
                m_hwnd = nullptr;
                return hr;
            }
            return 0;
        }

        case WM_SIZE:
        {
            m_d2dWindow.Resize(D2D1::SizeF(LOWORD(lParam), HIWORD(lParam)));
            InvalidateRect(m_hwnd, nullptr, FALSE);
            return 0;
        }

        case WM_ELEMENT_INVOKE:
            Invoke(wParam, lParam);
            return 0;

        case WM_ELEMENT_GETSTATUS:
            GetStatus(wParam, lParam);
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

void winWindow::SetSize(const Size size)
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
    InvalidateRect(m_hwnd, nullptr, FALSE);
}

Point winWindow::GetPosition() const
{
    return m_rect.GetPosition();
}

void winWindow::SetPosition(const Point position)
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

void winWindow::SetRectangle(const Rectangle rect)
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
    InvalidateRect(m_hwnd, nullptr, FALSE);
}

Color winWindow::GetBackgroundColor() const
{
    return m_backgroundColor;
}

void winWindow::SetBackgroundColor(const Color color)
{
    m_backgroundColor = color;
    const D2D1_COLOR_F d2dC_color
        = D2D1::ColorF(color.r, color.g, color.b, color.a);
    m_d2dWindow.SetClearColor(d2dC_color);

    InvalidateRect(m_hwnd, nullptr, FALSE);
}

void winWindow::Invoke(WPARAM wParam, const LPARAM lParam)
{
    switch (static_cast<WindowAction>(wParam))
    {
        case WindowAction::SHOW:
            Show();
            break;

        case WindowAction::HIDE:
            Hide();
            break;

        case WindowAction::MINIMIZE:
            Minimize();
            break;

        case WindowAction::MAXIMIZE:
            Maximize();
            break;

        case WindowAction::SIZE:
        {
            auto size = *reinterpret_cast<Size *>(lParam);
            if (typeid(size) != typeid(Size))
            {
                std::cout << "Invalid size" << std::endl;
                return;
            }
            SetSize(size);
            break;
        }

        case WindowAction::POSITION:
        {
            auto position = *reinterpret_cast<Point *>(lParam);
            if (typeid(position) != typeid(Point))
            {
                std::cout << "Invalid position" << std::endl;
                return;
            }
            SetPosition(position);
            break;
        }

        case WindowAction::RECTANGLE:
        {
            auto rect = *reinterpret_cast<Rectangle *>(lParam);
            if (typeid(rect) != typeid(Rectangle))
            {
                std::cout << "Invalid rectangle" << std::endl;
                return;
            }
            SetRectangle(rect);
            break;
        }

        case WindowAction::BACKGROUND_COLOR:
        {
            auto color = *reinterpret_cast<Color *>(lParam);
            if (typeid(color) != typeid(Color))
            {
                std::cout << "Invalid color" << std::endl;
                return;
            }
            SetBackgroundColor(color);
            break;
        }

        default:
            break;
    }
}

void winWindow::GetStatus(WPARAM wParam, const LPARAM lParam) const
{
    switch (static_cast<WindowAction>(wParam))
    {
        case WindowAction::ACTIVE:
        {
            auto *ptr = reinterpret_cast<bool *>(lParam);
            if (typeid(ptr) != typeid(bool *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = IsActive();
            break;
        }

        case WindowAction::SHOWSTATUS:
        {
            auto *ptr = reinterpret_cast<ShowStatus *>(lParam);
            if (typeid(ptr) != typeid(ShowStatus *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetShowStatus();
            break;
        }

        case WindowAction::HWND:
        {
            auto *ptr = reinterpret_cast<HWND *>(lParam);
            if (typeid(ptr) != typeid(HWND *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetHwnd();
            break;
        }

        case WindowAction::SIZE:
        {
            auto *ptr = reinterpret_cast<Size *>(lParam);
            if (typeid(ptr) != typeid(Size *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetSize();
            break;
        }

        case WindowAction::POSITION:
        {
            auto *ptr = reinterpret_cast<Point *>(lParam);
            if (typeid(ptr) != typeid(Point *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetPosition();
            break;
        }

        case WindowAction::RECTANGLE:
        {
            auto *ptr = reinterpret_cast<Rectangle *>(lParam);
            if (typeid(ptr) != typeid(Rectangle *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetRectangle();
            break;
        }

        case WindowAction::BACKGROUND_COLOR:
        {
            auto *ptr = reinterpret_cast<Color *>(lParam);
            if (typeid(ptr) != typeid(Color *))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetBackgroundColor();
            break;
        }

        default:
            break;
    }
}

}  // namespace element

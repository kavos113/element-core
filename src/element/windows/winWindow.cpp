#include "windows/winWindow.h"

#include <iostream>

namespace element
{

winWindow::~winWindow() = default;

HRESULT winWindow::RegisterWindowClass()
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
           .lpszClassName = CLASS_NAME,
           .hIconSm = LoadIcon(nullptr, IDI_APPLICATION)};

    ATOM const res = RegisterClassEx(&wc);
    if (res == 0)
    {
        std::cout << "Failed to register window class" << std::endl;
        return E_FAIL;
    }

    return S_OK;
}

HRESULT winWindow::UnregisterWindowClass()
{
    BOOL res = UnregisterClass(CLASS_NAME, GetModuleHandle(nullptr));
    if (res == 0)
    {
        std::cout << "Failed to unregister window class" << std::endl;
        return E_FAIL;
    }

    return S_OK;
}

HRESULT winWindow::Create(
    const wchar_t* title, int x, int y, int width, int height
)
{
    m_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
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

    m_rect = Rectangle(x, y, width, height);

    HRESULT hr = m_d2dWindow.Create(m_hwnd);
    if (FAILED(hr))
    {
        std::cout << "Failed to create Direct2D window" << std::endl;
        return hr;
    }

    return S_OK;
}

LRESULT winWindow::WinWindowProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam
)
{
    winWindow* pThis = nullptr;

    if (uMsg == WM_CREATE)
    {
        auto* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<winWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(
            hwnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pThis)
        );

        pThis->m_hwnd = hwnd;
    }
    else
    {
        pThis
            = reinterpret_cast<winWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)
            );
    }

    if (pThis != nullptr)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT winWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
        {
            BOOL res = DestroyWindow(m_hwnd);
            if (res == 0)
            {
                std::cout << "Failed to destroy window" << std::endl;
                return -1;
            }
            m_hwnd = nullptr;
            return 0;
        }

        case WM_PAINT:
            m_d2dWindow.BeginDraw();
            m_d2dWindow.EndDraw();
            return 0;

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

void winWindow::Invoke(WPARAM wParam, LPARAM lParam)
{
    switch (wParam)
    {
        case EL_WINDOW_SHOW:
            Show();
            break;

        case EL_WINDOW_HIDE:
            Hide();
            break;

        case EL_WINDOW_MINIMIZE:
            Minimize();
            break;

        case EL_WINDOW_MAXIMIZE:
            Maximize();
            break;

        case EL_WINDOW_SIZE:
        {
            auto size = *reinterpret_cast<Size*>(lParam);
            if (typeid(size) != typeid(Size))
            {
                std::cout << "Invalid size" << std::endl;
                return;
            }
            SetSize(size);
            break;
        }

        case EL_WINDOW_POSITION:
        {
            auto position = *reinterpret_cast<Point*>(lParam);
            if (typeid(position) != typeid(Point))
            {
                std::cout << "Invalid position" << std::endl;
                return;
            }
            SetPosition(position);
            break;
        }

        case EL_WINDOW_RECTANGLE:
        {
            auto rect = *reinterpret_cast<Rectangle*>(lParam);
            if (typeid(rect) != typeid(Rectangle))
            {
                std::cout << "Invalid rectangle" << std::endl;
                return;
            }
            SetRectangle(rect);
            break;
        }

        case EL_WINDOW_BACKGROUND_COLOR:
        {
            auto color = *reinterpret_cast<Color*>(lParam);
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

void winWindow::GetStatus(WPARAM wParam, LPARAM lParam) const
{
    switch (wParam)
    {
        case EL_WINDOW_ACTIVE:
        {
            auto ptr = reinterpret_cast<bool*>(lParam);
            if (typeid(ptr) != typeid(bool*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = IsActive();
            break;
        }

        case EL_WINDOW_SHOWSTATUS:
        {
            auto ptr = reinterpret_cast<ShowStatus*>(lParam);
            if (typeid(ptr) != typeid(ShowStatus*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetShowStatus();
            break;
        }

        case EL_WINDOW_HWND:
        {
            auto ptr = reinterpret_cast<HWND*>(lParam);
            if (typeid(ptr) != typeid(HWND*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetHwnd();
            break;
        }

        case EL_WINDOW_SIZE:
        {
            auto ptr = reinterpret_cast<Size*>(lParam);
            if (typeid(ptr) != typeid(Size*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetSize();
            break;
        }

        case EL_WINDOW_POSITION:
        {
            auto ptr = reinterpret_cast<Point*>(lParam);
            if (typeid(ptr) != typeid(Point*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetPosition();
            break;
        }

        case EL_WINDOW_RECTANGLE:
        {
            auto ptr = reinterpret_cast<Rectangle*>(lParam);
            if (typeid(ptr) != typeid(Rectangle*))
            {
                std::cout << "Invalid pointer" << std::endl;
                return;
            }
            *ptr = GetRectangle();
            break;
        }

        case EL_WINDOW_BACKGROUND_COLOR:
        {
            auto ptr = reinterpret_cast<Color*>(lParam);
            if (typeid(ptr) != typeid(Color*))
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

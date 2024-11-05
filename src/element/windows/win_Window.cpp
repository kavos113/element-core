#include "win_Window.h"

namespace element
{
    PCWSTR win_Window::ClassName() const
    {
        return L"Element Window";
    }
    
    LRESULT win_Window::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(m_hwnd, &ps);
                
                FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
                
                EndPaint(m_hwnd, &ps);
            }
            return 0;
        default:
            return DefWindowProc(m_hwnd, message, wParam, lParam);
        }
    }
    
    ATOM win_Window::RegisterNewClass()
    {
        WNDCLASS wc = {0};
        
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = ClassName();
        
        return RegisterClass(&wc);
    }
    
    BOOL win_Window::Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle,
        int x,
        int y,
        int nWidth,
        int nHeight,
        HWND hWndParent,
        HMENU hMenu
    )
    {
        m_hwnd = CreateWindowEx(
            dwExStyle,
            ClassName(),
            lpWindowName,
            dwStyle,
            x,
            y,
            nWidth,
            nHeight,
            hWndParent,
            hMenu,
            GetModuleHandle(nullptr),
            this
            );
        
        return (m_hwnd ? TRUE : FALSE);
    }
} // element
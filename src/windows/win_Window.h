#ifndef ELEMENT_WIN_WINDOW_H
#define ELEMENT_WIN_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

namespace element
{
    
    class win_Window
    {
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        win_Window* pWindow = nullptr;
        
        if (message == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pWindow = static_cast<win_Window*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
            
            pWindow->m_hwnd = hWnd;
        }
        else
        {
            pWindow = reinterpret_cast<win_Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }
        
        if (pWindow)
        {
            return pWindow->HandleMessage(message, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    
    win_Window() : m_hwnd(nullptr) {}
    
    private:
        PCWSTR ClassName() const;
        LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
        ATOM RegisterNewClass();
        BOOL Create(
            PCWSTR lpWindowName,
            DWORD dwStyle,
            DWORD dwExStyle = 0,
            int x = CW_USEDEFAULT,
            int y = CW_USEDEFAULT,
            int nWidth = CW_USEDEFAULT,
            int nHeight = CW_USEDEFAULT,
            HWND hWndParent = 0,
            HMENU hMenu = 0
            );
        
        HWND m_hwnd;
    };
    
} // element

#endif //ELEMENT_WIN_WINDOW_H

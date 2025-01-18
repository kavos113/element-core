#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

namespace element
{

class winWindow
{
   public:
    winWindow() = default;

    HRESULT Create(
        const wchar_t* title = L"",
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int width = CW_USEDEFAULT,
        int height = CW_USEDEFAULT
    );

   private:
    HWND m_hwnd{nullptr};
};

}  // namespace element

#endif  // WIN_WINDOW_H

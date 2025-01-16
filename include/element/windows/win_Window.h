#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H
#include <Windows.h>

namespace element
{

class win_Window
{
public:
    HRESULT Create(const wchar_t* title = L"", int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT);
};

}




#endif //WIN_WINDOW_H

#ifndef WINTEXT_H
#define WINTEXT_H

#ifndef UNICODE
#define UNICODE
#include <string>
#endif

#include <Windows.h>

namespace element
{

class winText
{
public:
    winText() = default;
    winText(const winText&) = delete;
    winText& operator=(const winText&) = delete;
    winText(winText&&) = delete;
    winText& operator=(winText&&) = delete;
    ~winText() = default;

    HRESULT Create(
        const std::wstring& text = L"",
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int width = CW_USEDEFAULT,
        int height = CW_USEDEFAULT
    );

private:
    std::wstring m_text;
};

}  // namespace element

#endif  // WINTEXT_H

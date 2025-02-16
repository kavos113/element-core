#ifndef ELEMENT_WINDOWS_WINTEXT_H
#define ELEMENT_WINDOWS_WINTEXT_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

#include <string>

#include "direct2d/dwriteText.h"

namespace element
{

class winText
{
public:
    winText() : m_text(L"")
    {
    }

    winText(const winText&) = delete;
    winText& operator=(const winText&) = delete;
    winText(winText&&) = default;
    winText& operator=(winText&&) = default;
    ~winText() = default;

    HRESULT Create(
        const std::wstring& text = L"",
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int width = CW_USEDEFAULT,
        int height = CW_USEDEFAULT
    );

    void Render(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& deviceContext
    );

private:
    std::wstring m_text;

    dwriteText m_dwriteText;
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_WINTEXT_H

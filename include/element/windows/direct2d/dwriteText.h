#ifndef ELEMENT_WINDOWS_DIRECT2D_DWRITETEXT_H
#define ELEMENT_WINDOWS_DIRECT2D_DWRITETEXT_H
#include <d2d1_1.h>
#include <dwrite.h>
#include <wrl/client.h>

#include <string>

namespace element
{

class dwriteText
{
public:
    dwriteText() = default;
    dwriteText(const dwriteText&) = delete;
    dwriteText& operator=(const dwriteText&) = delete;
    dwriteText(dwriteText&&) = delete;
    dwriteText& operator=(dwriteText&&) = delete;
    ~dwriteText() = default;

    HRESULT Create(const std::wstring& text, const D2D1_RECT_F& layout_rect);

    void Render(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& device_context
    );

    HRESULT SetText(const std::wstring& new_text);
    HRESULT SetSize(float width, float height);
    void SetPosition(float x, float y);
    HRESULT SetLayoutRect(D2D1_RECT_F rect);

    HRESULT SetFontSize(float size);
    HRESULT SetHorizontalAlignment(DWRITE_TEXT_ALIGNMENT alignment);

private:
    Microsoft::WRL::ComPtr<IDWriteTextLayout> m_textLayout;
    Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;

    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_textBrush;

    D2D1_RECT_F m_layoutRect = D2D1::RectF(0.0f, 0.0f, 0.0f, 0.0f);
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_DIRECT2D_DWRITETEXT_H

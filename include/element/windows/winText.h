#ifndef ELEMENT_WINDOWS_WINTEXT_H
#define ELEMENT_WINDOWS_WINTEXT_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

#include <string>

#include "color/Color.h"
#include "direct2d/dwriteText.h"
#include "font/Font.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Size.h"

namespace element
{

class winText
{
public:
    winText() : m_text(L""), m_font({})
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

    void Render();

    void SetDeviceContext(
        const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& deviceContext
    );

    [[nodiscard]] const std::wstring& GetText() const;
    HRESULT SetText(const std::wstring& new_text);
    [[nodiscard]] Size GetSize() const;
    HRESULT SetSize(Size size);
    [[nodiscard]] Point GetPosition() const;
    void SetPosition(Point position);
    [[nodiscard]] Rectangle GetRectangle() const;
    HRESULT SetRectangle(Rectangle rect);

    [[nodiscard]] float GetFontSize() const;
    HRESULT SetFontSize(float size);
    [[nodiscard]] Font::HorizontalAlignment GetHorizontalAlignment() const;
    HRESULT SetHorizontalAlignment(Font::HorizontalAlignment alignment);
    [[nodiscard]] Font::VerticalAlignment GetVerticalAlignment() const;
    HRESULT SetVerticalAlignment(Font::VerticalAlignment alignment);
    [[nodiscard]] std::wstring GetFontFamily() const;
    HRESULT SetFontFamily(const std::wstring& family);
    [[nodiscard]] Font::Style GetFontStyle() const;
    HRESULT SetFontStyle(Font::Style style);
    [[nodiscard]] Font::Stretch GetFontStretch() const;
    HRESULT SetFontStretch(Font::Stretch stretch);
    [[nodiscard]] Font::Weight GetFontWeight() const;
    HRESULT SetFontWeight(unsigned short weight);
    HRESULT SetFontWeight(Font::Weight weight);
    [[nodiscard]] Color GetColor() const;
    HRESULT SetColor(Color color);

private:
    std::wstring m_text;
    Font m_font;

    dwriteText m_dwriteText;

    Rectangle m_rect{};
    Color m_color{};

    Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_deviceContext;
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_WINTEXT_H

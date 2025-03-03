#ifndef ELEMENT_WINDOWS_WINTEXT_H
#define ELEMENT_WINDOWS_WINTEXT_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

#include <string>
#include <cstdint>

#include "color/Color.h"
#include "direct2d/dwriteText.h"
#include "font/Font.h"
#include "font/Paragraph.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Size.h"

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

    [[nodiscard]] Paragraph::HorizontalAlignment GetHorizontalAlignment() const;
    HRESULT SetHorizontalAlignment(Paragraph::HorizontalAlignment alignment);

    [[nodiscard]] Paragraph::VerticalAlignment GetVerticalAlignment() const;
    HRESULT SetVerticalAlignment(Paragraph::VerticalAlignment alignment);

    [[nodiscard]] std::wstring GetFontFamily() const;
    HRESULT SetFontFamily(const std::wstring& family);

    [[nodiscard]] Font::Style GetFontStyle() const;
    HRESULT SetFontStyle(Font::Style style);

    [[nodiscard]] Font::Stretch GetFontStretch() const;
    HRESULT SetFontStretch(Font::Stretch stretch);

    [[nodiscard]] Font::Weight GetFontWeight() const;
    HRESULT SetFontWeight(uint16_t weight);
    HRESULT SetFontWeight(Font::Weight weight);

    [[nodiscard]] Color GetColor() const;
    HRESULT SetColor(Color color);

    [[nodiscard]] float GetLineHeight() const;
    HRESULT SetLineHeight(float spacing);

    [[nodiscard]] Paragraph::Trimming GetTrimming() const;
    HRESULT SetTrimming(Paragraph::Trimming trimming);

    [[nodiscard]] Paragraph::Wrapping GetWordWrapping() const;
    HRESULT SetWordWrapping(Paragraph::Wrapping wrapping);

    [[nodiscard]] Paragraph::Direction GetFlowDirection() const;
    [[nodiscard]] Paragraph::Direction GetReadingDirection() const;
    HRESULT SetDirection(
        Paragraph::Direction flow_direction,
        Paragraph::Direction reading_direction
    );

    [[nodiscard]] bool IsUnderlined() const;
    HRESULT SetUnderline(bool underline);

    [[nodiscard]] bool IsLineThrough() const;
    HRESULT SetLineThrough(bool line_through);

private:
    std::wstring m_text;
    Paragraph m_paragraph;

    dwriteText m_dwriteText;

    Rectangle m_rect{};
    Color m_color{};

    Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_deviceContext;

    static constexpr uint16_t MIN_FONT_WEIGHT = 1;
    static constexpr uint16_t MAX_FONT_WEIGHT = 999;
    static constexpr uint16_t FONT_WEIGHT_THIN = 100;
    static constexpr uint16_t FONT_WEIGHT_EXTRA_LIGHT = 200;
    static constexpr uint16_t FONT_WEIGHT_LIGHT = 300;
    static constexpr uint16_t FONT_WEIGHT_SEMI_LIGHT = 350;
    static constexpr uint16_t FONT_WEIGHT_NORMAL = 400;
    static constexpr uint16_t FONT_WEIGHT_MEDIUM = 500;
    static constexpr uint16_t FONT_WEIGHT_SEMI_BOLD = 600;
    static constexpr uint16_t FONT_WEIGHT_BOLD = 700;
    static constexpr uint16_t FONT_WEIGHT_EXTRA_BOLD = 800;
    static constexpr uint16_t FONT_WEIGHT_BLACK = 900;
    static constexpr uint16_t FONT_WEIGHT_EXTRA_BLACK = 1000;
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_WINTEXT_H

#include "windows/winText.h"

namespace element
{

HRESULT winText::Create(
    const std::wstring& text,
    const int x,
    const int y,
    const int width,
    const int height
)
{
    m_text = text;

    HRESULT hr = m_dwriteText.Create(
        text,
        D2D1::RectF(
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(x + width),
            static_cast<float>(y + height)
        )
    );
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

void winText::Render()
{
    m_dwriteText.Render(m_deviceContext);
}

void winText::SetDeviceContext(
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& deviceContext
)
{
    m_deviceContext = deviceContext;
}

HRESULT winText::SetText(const std::wstring& new_text)
{
    HRESULT hr = m_dwriteText.SetText(new_text);
    if (FAILED(hr))
    {
        return hr;
    }

    m_text = new_text;

    return S_OK;
}

const std::wstring& winText::GetText() const
{
    return m_text;
}

Size winText::GetSize() const
{
    return m_rect.GetSize();
}

HRESULT winText::SetSize(const Size size)
{
    HRESULT hr = m_dwriteText.SetSize(size.width, size.height);
    if (FAILED(hr))
    {
        return hr;
    }

    m_rect.SetSize(size);
    return S_OK;
}

Point winText::GetPosition() const
{
    return m_rect.GetPosition();
}

void winText::SetPosition(const Point position)
{
    m_dwriteText.SetPosition(position.x, position.y);
    m_rect.SetPosition(position);
}

Rectangle winText::GetRectangle() const
{
    return m_rect;
}

HRESULT winText::SetRectangle(const Rectangle rect)
{
    HRESULT hr = m_dwriteText.SetLayoutRect(
        D2D1::RectF(rect.x, rect.y, rect.x + rect.width, rect.y + rect.height)
    );
    if (FAILED(hr))
    {
        return hr;
    }

    m_rect = rect;
    return S_OK;
}

float winText::GetFontSize() const
{
    return m_font.size;
}

HRESULT winText::SetFontSize(float size)
{
    HRESULT hr = m_dwriteText.SetFontSize(size);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.size = size;
    return S_OK;
}

Font::HorizontalAlignment winText::GetHorizontalAlignment() const
{
    return m_font.horizontal_alignment;
}

HRESULT winText::SetHorizontalAlignment(Font::HorizontalAlignment alignment)
{
    DWRITE_TEXT_ALIGNMENT dwrite_alignment;
    switch (alignment)
    {
        case Font::HorizontalAlignment::LEADING:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
            break;

        case Font::HorizontalAlignment::TRAILING:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_TRAILING;
            break;

        case Font::HorizontalAlignment::CENTER:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_CENTER;
            break;

        case Font::HorizontalAlignment::JUSTIFIED:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_JUSTIFIED;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetHorizontalAlignment(dwrite_alignment);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.horizontal_alignment = alignment;
    return S_OK;
}

Font::VerticalAlignment winText::GetVerticalAlignment() const
{
    return m_font.vertical_alignment;
}

HRESULT winText::SetVerticalAlignment(Font::VerticalAlignment alignment)
{
    DWRITE_PARAGRAPH_ALIGNMENT dwrite_alignment;
    switch (alignment)
    {
        case Font::VerticalAlignment::TOP:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
            break;

        case Font::VerticalAlignment::CENTER:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
            break;

        case Font::VerticalAlignment::BOTTOM:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_FAR;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetVerticalAlignment(dwrite_alignment);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.vertical_alignment = alignment;
    return S_OK;
}

std::wstring winText::GetFontFamily() const
{
    return m_font.family;
}

HRESULT winText::SetFontFamily(const std::wstring& family)
{
    HRESULT hr = m_dwriteText.SetFontFamily(family);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.family = family;
    return S_OK;
}

Font::Style winText::GetFontStyle() const
{
    return m_font.style;
}

HRESULT winText::SetFontStyle(Font::Style style)
{
    DWRITE_FONT_STYLE dwrite_style;
    switch (style)
    {
        case Font::Style::NORMAL:
            dwrite_style = DWRITE_FONT_STYLE_NORMAL;
            break;

        case Font::Style::ITALIC:
            dwrite_style = DWRITE_FONT_STYLE_ITALIC;
            break;

        case Font::Style::OBLIQUE:
            dwrite_style = DWRITE_FONT_STYLE_OBLIQUE;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetFontStyle(dwrite_style);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.style = style;
    return S_OK;
}

Font::Stretch winText::GetFontStretch() const
{
    return m_font.stretch;
}

HRESULT winText::SetFontStretch(Font::Stretch stretch)
{
    DWRITE_FONT_STRETCH dwrite_stretch;
    switch (stretch)
    {
        case Font::Stretch::ULTRA_CONDENSED:
            dwrite_stretch = DWRITE_FONT_STRETCH_ULTRA_CONDENSED;
            break;

        case Font::Stretch::EXTRA_CONDENSED:
            dwrite_stretch = DWRITE_FONT_STRETCH_EXTRA_CONDENSED;
            break;

        case Font::Stretch::CONDENSED:
            dwrite_stretch = DWRITE_FONT_STRETCH_CONDENSED;
            break;

        case Font::Stretch::SEMI_CONDENSED:
            dwrite_stretch = DWRITE_FONT_STRETCH_SEMI_CONDENSED;
            break;

        case Font::Stretch::NORMAL:
            dwrite_stretch = DWRITE_FONT_STRETCH_NORMAL;
            break;

        case Font::Stretch::SEMI_EXPANDED:
            dwrite_stretch = DWRITE_FONT_STRETCH_SEMI_EXPANDED;
            break;

        case Font::Stretch::EXPANDED:
            dwrite_stretch = DWRITE_FONT_STRETCH_EXPANDED;
            break;

        case Font::Stretch::EXTRA_EXPANDED:
            dwrite_stretch = DWRITE_FONT_STRETCH_EXTRA_EXPANDED;
            break;

        case Font::Stretch::ULTRA_EXPANDED:
            dwrite_stretch = DWRITE_FONT_STRETCH_ULTRA_EXPANDED;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetFontStretch(dwrite_stretch);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.stretch = stretch;
    return S_OK;
}

Font::Weight winText::GetFontWeight() const
{
    return m_font.weight;
}

HRESULT winText::SetFontWeight(unsigned short weight)
{
    if (weight < 1 || weight > 999)
    {
        return E_INVALIDARG;
    }

    Font::Weight font_weight;
    if (weight < 150)
    {
        font_weight = Font::Weight::THIN;
    }
    else if (weight < 250)
    {
        font_weight = Font::Weight::EXTRA_LIGHT;
    }
    else if (weight < 325)
    {
        font_weight = Font::Weight::LIGHT;
    }
    else if (weight < 375)
    {
        font_weight = Font::Weight::SEMI_LIGHT;
    }
    else if (weight < 450)
    {
        font_weight = Font::Weight::NORMAL;
    }
    else if (weight < 550)
    {
        font_weight = Font::Weight::MEDIUM;
    }
    else if (weight < 650)
    {
        font_weight = Font::Weight::SEMI_BOLD;
    }
    else if (weight < 750)
    {
        font_weight = Font::Weight::BOLD;
    }
    else if (weight < 850)
    {
        font_weight = Font::Weight::EXTRA_BOLD;
    }
    else if (weight < 950)
    {
        font_weight = Font::Weight::BLACK;
    }
    else
    {
        font_weight = Font::Weight::EXTRA_BLACK;
    }

    HRESULT hr = SetFontWeight(font_weight);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

HRESULT winText::SetFontWeight(Font::Weight weight)
{
    DWRITE_FONT_WEIGHT dwrite_weight;
    switch (weight)
    {
        case Font::Weight::THIN:
            dwrite_weight = DWRITE_FONT_WEIGHT_THIN;
            break;

        case Font::Weight::EXTRA_LIGHT:
            dwrite_weight = DWRITE_FONT_WEIGHT_EXTRA_LIGHT;
            break;

        case Font::Weight::LIGHT:
            dwrite_weight = DWRITE_FONT_WEIGHT_LIGHT;
            break;

        case Font::Weight::SEMI_LIGHT:
            dwrite_weight = DWRITE_FONT_WEIGHT_SEMI_LIGHT;
            break;

        case Font::Weight::NORMAL:
            dwrite_weight = DWRITE_FONT_WEIGHT_NORMAL;
            break;

        case Font::Weight::MEDIUM:
            dwrite_weight = DWRITE_FONT_WEIGHT_MEDIUM;
            break;

        case Font::Weight::SEMI_BOLD:
            dwrite_weight = DWRITE_FONT_WEIGHT_SEMI_BOLD;
            break;

        case Font::Weight::BOLD:
            dwrite_weight = DWRITE_FONT_WEIGHT_BOLD;
            break;

        case Font::Weight::EXTRA_BOLD:
            dwrite_weight = DWRITE_FONT_WEIGHT_EXTRA_BOLD;
            break;

        case Font::Weight::BLACK:
            dwrite_weight = DWRITE_FONT_WEIGHT_BLACK;
            break;

        case Font::Weight::EXTRA_BLACK:
            dwrite_weight = DWRITE_FONT_WEIGHT_EXTRA_BLACK;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetFontWeight(dwrite_weight);
    if (FAILED(hr))
    {
        return hr;
    }

    m_font.weight = weight;
    return S_OK;
}

Color winText::GetColor() const
{
    return m_color;
}

HRESULT winText::SetColor(Color color)
{
    HRESULT hr = m_dwriteText.SetFontColor(
        D2D1_COLOR_F(color.r, color.g, color.b, color.a),
        m_deviceContext
    );
    if (FAILED(hr))
    {
        return hr;
    }

    m_color = color;
    return S_OK;
}

}  // namespace element
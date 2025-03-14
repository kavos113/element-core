#include "windows/winText.h"

namespace karin
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

    const HRESULT hr = m_dwriteText.Create(
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
    const HRESULT hr = m_dwriteText.SetText(new_text);
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
    const HRESULT hr = m_dwriteText.SetSize(size.width, size.height);
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
    const HRESULT hr = m_dwriteText.SetLayoutRect(
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
    return m_paragraph.font.size;
}

HRESULT winText::SetFontSize(const float size)
{
    const HRESULT hr = m_dwriteText.SetFontSize(size);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.size = size;
    return S_OK;
}

Paragraph::HorizontalAlignment winText::GetHorizontalAlignment() const
{
    return m_paragraph.horizontal_alignment;
}

HRESULT winText::SetHorizontalAlignment(
    const Paragraph::HorizontalAlignment alignment
)
{
    DWRITE_TEXT_ALIGNMENT dwrite_alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
    switch (alignment)
    {
        case Paragraph::HorizontalAlignment::LEADING:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_LEADING;
            break;

        case Paragraph::HorizontalAlignment::TRAILING:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_TRAILING;
            break;

        case Paragraph::HorizontalAlignment::CENTER:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_CENTER;
            break;

        case Paragraph::HorizontalAlignment::JUSTIFIED:
            dwrite_alignment = DWRITE_TEXT_ALIGNMENT_JUSTIFIED;
            break;

        default:
            return E_INVALIDARG;
    }

    const HRESULT hr = m_dwriteText.SetHorizontalAlignment(dwrite_alignment);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.horizontal_alignment = alignment;
    return S_OK;
}

Paragraph::VerticalAlignment winText::GetVerticalAlignment() const
{
    return m_paragraph.vertical_alignment;
}

HRESULT winText::SetVerticalAlignment(
    const Paragraph::VerticalAlignment alignment
)
{
    DWRITE_PARAGRAPH_ALIGNMENT dwrite_alignment
        = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
    switch (alignment)
    {
        case Paragraph::VerticalAlignment::TOP:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
            break;

        case Paragraph::VerticalAlignment::CENTER:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
            break;

        case Paragraph::VerticalAlignment::BOTTOM:
            dwrite_alignment = DWRITE_PARAGRAPH_ALIGNMENT_FAR;
            break;

        default:
            return E_INVALIDARG;
    }

    const HRESULT hr = m_dwriteText.SetVerticalAlignment(dwrite_alignment);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.vertical_alignment = alignment;
    return S_OK;
}

std::wstring winText::GetFontFamily() const
{
    return m_paragraph.font.family;
}

HRESULT winText::SetFontFamily(const std::wstring& family)
{
    const HRESULT hr = m_dwriteText.SetFontFamily(family);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.family = family;
    return S_OK;
}

Font::Style winText::GetFontStyle() const
{
    return m_paragraph.font.style;
}

HRESULT winText::SetFontStyle(const Font::Style style)
{
    DWRITE_FONT_STYLE dwrite_style = DWRITE_FONT_STYLE_NORMAL;
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

    const HRESULT hr = m_dwriteText.SetFontStyle(dwrite_style);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.style = style;
    return S_OK;
}

Font::Stretch winText::GetFontStretch() const
{
    return m_paragraph.font.stretch;
}

HRESULT winText::SetFontStretch(const Font::Stretch stretch)
{
    DWRITE_FONT_STRETCH dwrite_stretch = DWRITE_FONT_STRETCH_NORMAL;
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

    const HRESULT hr = m_dwriteText.SetFontStretch(dwrite_stretch);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.stretch = stretch;
    return S_OK;
}

Font::Weight winText::GetFontWeight() const
{
    return m_paragraph.font.weight;
}

HRESULT winText::SetFontWeight(const uint16_t weight)
{
    if (weight < MIN_FONT_WEIGHT || weight > MAX_FONT_WEIGHT)
    {
        return E_INVALIDARG;
    }

    Font::Weight font_weight = Font::Weight::NORMAL;
    if (weight < (FONT_WEIGHT_THIN + FONT_WEIGHT_EXTRA_LIGHT) / 2)
    {
        font_weight = Font::Weight::THIN;
    }
    else if (weight < (FONT_WEIGHT_EXTRA_LIGHT + FONT_WEIGHT_LIGHT) / 2)
    {
        font_weight = Font::Weight::EXTRA_LIGHT;
    }
    else if (weight < (FONT_WEIGHT_LIGHT + FONT_WEIGHT_SEMI_LIGHT) / 2)
    {
        font_weight = Font::Weight::LIGHT;
    }
    else if (weight < (FONT_WEIGHT_SEMI_LIGHT + FONT_WEIGHT_NORMAL) / 2)
    {
        font_weight = Font::Weight::SEMI_LIGHT;
    }
    else if (weight < (FONT_WEIGHT_NORMAL + FONT_WEIGHT_MEDIUM) / 2)
    {
        font_weight = Font::Weight::NORMAL;
    }
    else if (weight < (FONT_WEIGHT_MEDIUM + FONT_WEIGHT_SEMI_BOLD) / 2)
    {
        font_weight = Font::Weight::MEDIUM;
    }
    else if (weight < (FONT_WEIGHT_SEMI_BOLD + FONT_WEIGHT_BOLD) / 2)
    {
        font_weight = Font::Weight::SEMI_BOLD;
    }
    else if (weight < (FONT_WEIGHT_BOLD + FONT_WEIGHT_EXTRA_BOLD) / 2)
    {
        font_weight = Font::Weight::BOLD;
    }
    else if (weight < (FONT_WEIGHT_EXTRA_BOLD + FONT_WEIGHT_BLACK) / 2)
    {
        font_weight = Font::Weight::EXTRA_BOLD;
    }
    else if (weight < (FONT_WEIGHT_BLACK + FONT_WEIGHT_EXTRA_BLACK) / 2)
    {
        font_weight = Font::Weight::BLACK;
    }
    else
    {
        font_weight = Font::Weight::EXTRA_BLACK;
    }

    const HRESULT hr = SetFontWeight(font_weight);
    if (FAILED(hr))
    {
        return hr;
    }

    return S_OK;
}

HRESULT winText::SetFontWeight(const Font::Weight weight)
{
    DWRITE_FONT_WEIGHT dwrite_weight = DWRITE_FONT_WEIGHT_NORMAL;
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

    const HRESULT hr = m_dwriteText.SetFontWeight(dwrite_weight);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.weight = weight;
    return S_OK;
}

Color winText::GetColor() const
{
    return m_color;
}

HRESULT winText::SetColor(const Color color)
{
    const HRESULT hr = m_dwriteText.SetFontColor(
        D2D1_COLOR_F(color.r, color.g, color.b, color.a)
    );
    if (FAILED(hr))
    {
        return hr;
    }

    m_color = color;
    return S_OK;
}

float winText::GetLineHeight() const
{
    return m_paragraph.line_spacing;
}

HRESULT winText::SetLineHeight(const float spacing)
{
    const HRESULT hr = m_dwriteText.SetLineSpacing(spacing);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.line_spacing = spacing;
    return S_OK;
}

Paragraph::Trimming winText::GetTrimming() const
{
    return m_paragraph.trimming;
}

HRESULT winText::SetTrimming(const Paragraph::Trimming trimming)
{
    DWRITE_TRIMMING_GRANULARITY dwrite_trimming
        = DWRITE_TRIMMING_GRANULARITY_NONE;
    switch (trimming)
    {
        case Paragraph::Trimming::NONE:
            dwrite_trimming = DWRITE_TRIMMING_GRANULARITY_NONE;
            break;

        case Paragraph::Trimming::WORD:
            dwrite_trimming = DWRITE_TRIMMING_GRANULARITY_WORD;
            break;

        case Paragraph::Trimming::CHARACTER:
            dwrite_trimming = DWRITE_TRIMMING_GRANULARITY_CHARACTER;
            break;

        default:
            return E_INVALIDARG;
    }

    const HRESULT hr = m_dwriteText.SetTrimming(dwrite_trimming);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.trimming = trimming;
    return S_OK;
}

Paragraph::Wrapping winText::GetWordWrapping() const
{
    return m_paragraph.wrapping;
}

HRESULT winText::SetWordWrapping(const Paragraph::Wrapping wrapping)
{
    DWRITE_WORD_WRAPPING dwrite_wrapping = DWRITE_WORD_WRAPPING_NO_WRAP;
    switch (wrapping)
    {
        case Paragraph::Wrapping::NONE:
            dwrite_wrapping = DWRITE_WORD_WRAPPING_NO_WRAP;
            break;

        case Paragraph::Wrapping::WORD:
            dwrite_wrapping = DWRITE_WORD_WRAPPING_WRAP;
            break;

        case Paragraph::Wrapping::CHARACTER:
            dwrite_wrapping = DWRITE_WORD_WRAPPING_CHARACTER;
            break;

        default:
            return E_INVALIDARG;
    }

    const HRESULT hr = m_dwriteText.SetWordWrapping(dwrite_wrapping);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.wrapping = wrapping;
    return S_OK;
}

Paragraph::Direction winText::GetFlowDirection() const
{
    return m_paragraph.flow_direction;
}

Paragraph::Direction winText::GetReadingDirection() const
{
    return m_paragraph.reading_direction;
}

HRESULT winText::SetDirection(
    const Paragraph::Direction flow_direction,
    const Paragraph::Direction reading_direction
)
{
    if (flow_direction == Paragraph::Direction::RIGHT_TO_LEFT
        && reading_direction == Paragraph::Direction::LEFT_TO_RIGHT)
    {
        return E_INVALIDARG;
    }

    if (flow_direction == Paragraph::Direction::LEFT_TO_RIGHT
        && reading_direction == Paragraph::Direction::RIGHT_TO_LEFT)
    {
        return E_INVALIDARG;
    }

    if (flow_direction == Paragraph::Direction::TOP_TO_BOTTOM
        && reading_direction == Paragraph::Direction::BOTTOM_TO_TOP)
    {
        return E_INVALIDARG;
    }

    if (flow_direction == Paragraph::Direction::BOTTOM_TO_TOP
        && reading_direction == Paragraph::Direction::TOP_TO_BOTTOM)
    {
        return E_INVALIDARG;
    }

    if (flow_direction == reading_direction)
    {
        return E_INVALIDARG;
    }

    DWRITE_FLOW_DIRECTION dwrite_flow_direction
        = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM;
    switch (flow_direction)
    {
        case Paragraph::Direction::TOP_TO_BOTTOM:
            dwrite_flow_direction = DWRITE_FLOW_DIRECTION_TOP_TO_BOTTOM;
            break;

        case Paragraph::Direction::BOTTOM_TO_TOP:
            dwrite_flow_direction = DWRITE_FLOW_DIRECTION_BOTTOM_TO_TOP;
            break;

        case Paragraph::Direction::LEFT_TO_RIGHT:
            dwrite_flow_direction = DWRITE_FLOW_DIRECTION_LEFT_TO_RIGHT;
            break;

        case Paragraph::Direction::RIGHT_TO_LEFT:
            dwrite_flow_direction = DWRITE_FLOW_DIRECTION_RIGHT_TO_LEFT;
            break;

        default:
            return E_INVALIDARG;
    }

    DWRITE_READING_DIRECTION dwrite_reading_direction
        = DWRITE_READING_DIRECTION_TOP_TO_BOTTOM;
    switch (reading_direction)
    {
        case Paragraph::Direction::TOP_TO_BOTTOM:
            dwrite_reading_direction = DWRITE_READING_DIRECTION_TOP_TO_BOTTOM;
            break;

        case Paragraph::Direction::BOTTOM_TO_TOP:
            dwrite_reading_direction = DWRITE_READING_DIRECTION_BOTTOM_TO_TOP;
            break;

        case Paragraph::Direction::LEFT_TO_RIGHT:
            dwrite_reading_direction = DWRITE_READING_DIRECTION_LEFT_TO_RIGHT;
            break;

        case Paragraph::Direction::RIGHT_TO_LEFT:
            dwrite_reading_direction = DWRITE_READING_DIRECTION_RIGHT_TO_LEFT;
            break;

        default:
            return E_INVALIDARG;
    }

    HRESULT hr = m_dwriteText.SetFlowDirection(dwrite_flow_direction);
    if (FAILED(hr))
    {
        return hr;
    }

    hr = m_dwriteText.SetReadingDirection(dwrite_reading_direction);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.flow_direction = flow_direction;
    m_paragraph.reading_direction = reading_direction;

    return S_OK;
}

bool winText::IsUnderlined() const
{
    return m_paragraph.font.underline;
}

HRESULT winText::SetUnderline(const bool underline)
{
    const HRESULT hr = m_dwriteText.SetUnderline(underline);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.underline = underline;
    return S_OK;
}

bool winText::IsLineThrough() const
{
    return m_paragraph.font.line_through;
}

HRESULT winText::SetLineThrough(const bool line_through)
{
    const HRESULT hr = m_dwriteText.SetLineThrough(line_through);
    if (FAILED(hr))
    {
        return hr;
    }

    m_paragraph.font.line_through = line_through;
    return S_OK;
}

}  // namespace karin
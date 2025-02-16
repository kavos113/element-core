#include "windows/direct2d/dwriteText.h"

#include <iostream>

#include "windows/direct2d/dwriteFactory.h"

namespace element
{

HRESULT dwriteText::Create(
    const std::wstring& text, const D2D1_RECT_F& layoutRect
)
{
    m_layoutRect = layoutRect;

    HRESULT hr = dwriteFactory::Get()->CreateTextFormat(
        L"Segoe UI",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        24.0f,
        L"en-us",
        m_textFormat.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create text format" << std::endl;
        return hr;
    }

    hr = dwriteFactory::Get()->CreateTextLayout(
        text.c_str(),
        static_cast<UINT32>(text.length()),
        m_textFormat.Get(),
        layoutRect.right - layoutRect.left,
        layoutRect.bottom - layoutRect.top,
        m_textLayout.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create text layout" << std::endl;
        return hr;
    }

    return S_OK;
}

void dwriteText::Render(
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& deviceContext
)
{
    if (m_textBrush == nullptr)
    {
        const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
        deviceContext->CreateSolidColorBrush(color, m_textBrush.GetAddressOf());
    }

    const D2D1_POINT_2F origin
        = D2D1::Point2F(m_layoutRect.left, m_layoutRect.top);

    deviceContext
        ->DrawTextLayout(origin, m_textLayout.Get(), m_textBrush.Get());
}

HRESULT dwriteText::SetText(const std::wstring& new_text)
{
    const HRESULT hr = dwriteFactory::Get()->CreateTextLayout(
        new_text.c_str(),
        static_cast<UINT32>(new_text.length()),
        m_textFormat.Get(),
        m_layoutRect.right - m_layoutRect.left,
        m_layoutRect.bottom - m_layoutRect.top,
        m_textLayout.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create text layout" << std::endl;
        return hr;
    }

    return S_OK;
}

HRESULT dwriteText::SetSize(const float width, float height)
{
    HRESULT hr = m_textLayout->SetMaxWidth(width);
    if (FAILED(hr))
    {
        std::cout << "Failed to set max width" << std::endl;
        return hr;
    }

    hr = m_textLayout->SetMaxHeight(height);
    if (FAILED(hr))
    {
        std::cout << "Failed to set max height" << std::endl;
        return hr;
    }

    m_layoutRect.right = m_layoutRect.left + width;
    m_layoutRect.bottom = m_layoutRect.top + height;

    return S_OK;
}

void dwriteText::SetPosition(float x, float y)
{
    m_layoutRect.right = x + m_layoutRect.right - m_layoutRect.left;
    m_layoutRect.bottom = y + m_layoutRect.bottom - m_layoutRect.top;
    m_layoutRect.left = x;
    m_layoutRect.top = y;
}

HRESULT dwriteText::SetLayoutRect(D2D1_RECT_F rect)
{
    HRESULT hr = m_textLayout->SetMaxWidth(rect.right - rect.left);
    if (FAILED(hr))
    {
        std::cout << "Failed to set max width" << std::endl;
        return hr;
    }

    hr = m_textLayout->SetMaxHeight(rect.bottom - rect.top);
    if (FAILED(hr))
    {
        std::cout << "Failed to set max height" << std::endl;
        return hr;
    }

    m_layoutRect = rect;

    return S_OK;
}

HRESULT dwriteText::SetFontSize(const float size)
{
    const DWRITE_TEXT_RANGE text_range
        = {0, static_cast<UINT32>(m_textLayout->GetMaxWidth())};
    const HRESULT hr = m_textLayout->SetFontSize(size, text_range);
    if (FAILED(hr))
    {
        std::cout << "Failed to set font size" << std::endl;
        return hr;
    }

    return S_OK;
}

HRESULT dwriteText::SetHorizontalAlignment(DWRITE_TEXT_ALIGNMENT alignment)
{
    HRESULT hr = m_textLayout->SetTextAlignment(alignment);
    if (FAILED(hr))
    {
        std::cout << "Failed to set text alignment" << std::endl;
        return hr;
    }

    return S_OK;
}

HRESULT dwriteText::SetVerticalAlignment(DWRITE_PARAGRAPH_ALIGNMENT alignment)
{
    HRESULT hr = m_textLayout->SetParagraphAlignment(alignment);
    if (FAILED(hr))
    {
        std::cout << "Failed to set paragraph alignment" << std::endl;
        return hr;
    }

    return S_OK;
}

}  // namespace element
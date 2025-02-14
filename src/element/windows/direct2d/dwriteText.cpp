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

    Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat = nullptr;
    HRESULT hr = dwriteFactory::Get()->CreateTextFormat(
        L"Segoe UI",
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        24.0f,
        L"en-us",
        textFormat.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create text format" << std::endl;
        return hr;
    }

    hr = dwriteFactory::Get()->CreateTextLayout(
        text.c_str(),
        static_cast<UINT32>(text.length()),
        textFormat.Get(),
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

    D2D1_POINT_2F origin = D2D1::Point2F(m_layoutRect.left, m_layoutRect.top);

    deviceContext
        ->DrawTextLayout(origin, m_textLayout.Get(), m_textBrush.Get());
}

}  // namespace element
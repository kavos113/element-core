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

void winText::Render(
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& device_context
)
{
    m_dwriteText.Render(device_context);
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

}  // namespace element
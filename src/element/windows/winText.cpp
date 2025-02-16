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

}  // namespace element
#include "windows/winText.h"

namespace element
{

HRESULT winText::Create(
    const std::wstring& text, int x, int y, int width, int height
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
    const Microsoft::WRL::ComPtr<ID2D1DeviceContext>& deviceContext
)
{
    m_dwriteText.Render(deviceContext);
}

}  // namespace element
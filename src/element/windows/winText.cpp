#include "windows/winText.h"

namespace element
{

HRESULT winText::Create(
    const std::wstring& text, int x, int y, int width, int height
)
{
    m_text = text;

    return S_OK;
}

}  // namespace element
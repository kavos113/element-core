#ifndef D2DWINDOW_H
#define D2DWINDOW_H
#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace element
{

class d2dWindow
{
public:
    d2dWindow()
        : m_deviceContext(nullptr), m_bitmap(nullptr), m_swapChain(nullptr)
    {
    }

    ~d2dWindow() = default;

    HRESULT Create(HWND hwnd);

    void BeginDraw();
    HRESULT EndDraw();

    Microsoft::WRL::ComPtr<ID2D1DeviceContext7> GetDeviceContext() const;

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext7> m_deviceContext;
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;
};

}  // namespace element

#endif  // D2DWINDOW_H

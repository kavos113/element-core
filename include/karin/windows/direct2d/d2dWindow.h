#ifndef KARIN_WINDOWS_DIRECT2D_D2DWINDOW_H
#define KARIN_WINDOWS_DIRECT2D_D2DWINDOW_H

#include <d2d1_1.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace karin
{

class d2dWindow
{
public:
    d2dWindow() : m_deviceContext(nullptr), m_swapChain(nullptr)
    {
    }

    ~d2dWindow() = default;
    d2dWindow(const d2dWindow&) = delete;
    d2dWindow& operator=(const d2dWindow&) = delete;
    d2dWindow(d2dWindow&&) = delete;
    d2dWindow& operator=(d2dWindow&&) = delete;

    HRESULT Create(HWND hwnd);

    void BeginDraw() const;
    [[nodiscard]] HRESULT EndDraw() const;

    void Resize(D2D1_SIZE_F size) const;

    void SetClearColor(D2D1_COLOR_F color);

    [[nodiscard]] Microsoft::WRL::ComPtr<ID2D1DeviceContext> GetDeviceContext(
    ) const;

private:
    Microsoft::WRL::ComPtr<ID2D1DeviceContext> m_deviceContext;
    Microsoft::WRL::ComPtr<IDXGISwapChain1> m_swapChain;

    D2D1_COLOR_F m_clearColor = D2D1::ColorF(D2D1::ColorF::White);

    static constexpr float dpi_x = 96.0f;
    static constexpr float dpi_y = 96.0f;
};

}  // namespace karin

#endif  // KARIN_WINDOWS_DIRECT2D_D2DWINDOW_H

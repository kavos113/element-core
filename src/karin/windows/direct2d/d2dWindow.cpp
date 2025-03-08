#include "windows/direct2d/d2dWindow.h"

#include <iostream>

#include "windows/direct2d/d2dDevice.h"
#include "windows/direct2d/dxgiDevice.h"

namespace karin
{

HRESULT d2dWindow::Create(HWND hwnd)
{
    constexpr DXGI_SWAP_CHAIN_DESC1 desc = {
        .Width = 0,
        .Height = 0,
        .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
        .Stereo = FALSE,
        .SampleDesc = {.Count = 1, .Quality = 0},
        .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount = 2,
        .Scaling = DXGI_SCALING_NONE,
        .SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
        .AlphaMode = DXGI_ALPHA_MODE_IGNORE,
        .Flags = 0,
    };

    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter = nullptr;
    HRESULT hr = dxgiDevice::Get()->GetAdapter(adapter.GetAddressOf());
    if (FAILED(hr))
    {
        std::cout << "Failed to get DXGI adapter" << std::endl;
        return hr;
    }

    Microsoft::WRL::ComPtr<IDXGIFactory2> factory = nullptr;
    hr = adapter->GetParent(IID_PPV_ARGS(&factory));
    if (FAILED(hr))
    {
        std::cout << "Failed to get DXGI factory" << std::endl;
        return hr;
    }

    hr = factory->CreateSwapChainForHwnd(
        dxgiDevice::Get().Get(),
        hwnd,
        &desc,
        nullptr,
        nullptr,
        m_swapChain.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create swap chain" << std::endl;
        return hr;
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr))
    {
        std::cout << "Failed to get back buffer" << std::endl;
        return hr;
    }

    const D2D1_BITMAP_PROPERTIES1 properties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
        dpi_x,
        dpi_y
    );

    Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface = nullptr;
    hr = backBuffer->QueryInterface(dxgiSurface.GetAddressOf());
    if (FAILED(hr))
    {
        std::cout << "Failed to get DXGI surface" << std::endl;
        return hr;
    }

    hr = d2dDevice::Get()->CreateDeviceContext(
        D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
        m_deviceContext.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create Direct2D device context" << std::endl;
        return hr;
    }

    Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap = nullptr;
    hr = m_deviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface.Get(),
        properties,
        bitmap.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create bitmap from DXGI surface" << std::endl;
        return hr;
    }

    m_deviceContext->SetTarget(bitmap.Get());

    return S_OK;
}

void d2dWindow::Resize(const D2D1_SIZE_F size) const
{
    m_deviceContext->SetTarget(nullptr);

    HRESULT hr = m_swapChain->ResizeBuffers(
        0,
        static_cast<UINT>(size.width),
        static_cast<UINT>(size.height),
        DXGI_FORMAT_B8G8R8A8_UNORM,
        0
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to resize buffers" << std::endl;
        return;
    }

    Microsoft::WRL::ComPtr<IDXGISurface> dxgi_surface = nullptr;
    hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgi_surface));
    if (FAILED(hr))
    {
        std::cout << "Failed to get buffer" << std::endl;
        return;
    }

    Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap = nullptr;
    hr = m_deviceContext->CreateBitmapFromDxgiSurface(
        dxgi_surface.Get(),
        D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
            D2D1::PixelFormat(
                DXGI_FORMAT_B8G8R8A8_UNORM,
                D2D1_ALPHA_MODE_IGNORE
            ),
            dpi_x,
            dpi_y
        ),
        bitmap.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create bitmap from DXGI surface" << std::endl;
        return;
    }

    m_deviceContext->SetTarget(bitmap.Get());
}

Microsoft::WRL::ComPtr<ID2D1DeviceContext> d2dWindow::GetDeviceContext() const
{
    return m_deviceContext;
}

void d2dWindow::BeginDraw() const
{
    m_deviceContext->BeginDraw();
    m_deviceContext->Clear(m_clearColor);
}

HRESULT d2dWindow::EndDraw() const
{
    HRESULT hr = m_deviceContext->EndDraw();
    if (FAILED(hr))
    {
        std::cout << "Failed to end draw" << std::endl;
        return hr;
    }

    hr = m_swapChain->Present(1, 0);
    if (FAILED(hr))
    {
        std::cout << "Failed to present" << std::endl;
        return hr;
    }

    return hr;
}

void d2dWindow::SetClearColor(const D2D1_COLOR_F color)
{
    m_clearColor = color;
}

}  // namespace karin
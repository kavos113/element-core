#include "windows/direct2d/d2dWindow.h"

#include <iostream>

#include "windows/direct2d/d2dDevice.h"
#include "windows/direct2d/dxgiDevice.h"

namespace element
{

HRESULT d2dWindow::Create(HWND hwnd)
{
    DXGI_SWAP_CHAIN_DESC1 desc = {
        .Width = 0,
        .Height = 0,
        .Format = DXGI_FORMAT_B8G8R8A8_UNORM,
        .Stereo = false,
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

    D2D1_BITMAP_PROPERTIES1 properties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
        96.0f,
        96.0f
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

    hr = m_deviceContext->CreateBitmapFromDxgiSurface(
        dxgiSurface.Get(),
        properties,
        m_bitmap.GetAddressOf()
    );
    if (FAILED(hr))
    {
        std::cout << "Failed to create bitmap from DXGI surface" << std::endl;
        return hr;
    }

    m_deviceContext->SetTarget(m_bitmap.Get());

    return S_OK;
}

Microsoft::WRL::ComPtr<ID2D1DeviceContext7> d2dWindow::GetDeviceContext() const
{
    return m_deviceContext;
}

}  // namespace element
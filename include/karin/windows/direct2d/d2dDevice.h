#ifndef KARIN_WINDOWS_DIRECT2D_D2DDEVICE_H
#define KARIN_WINDOWS_DIRECT2D_D2DDEVICE_H
#include <d2d1_1.h>
#include <d3d11.h>
#include <wrl/client.h>

#include <iostream>

#include "d2dFactory.h"
#include "dxgiDevice.h"

namespace karin
{

class d2dDevice
{
public:
    static Microsoft::WRL::ComPtr<ID2D1Device>& Get()
    {
        static Microsoft::WRL::ComPtr<ID2D1Device> device = nullptr;
        if (device == nullptr)
        {
            CreateDevice(&device);
        }

        return device;
    }

private:
    static void CreateDevice(ID2D1Device** device)
    {
        const HRESULT hr
            = d2dFactory::Get()->CreateDevice(dxgiDevice::Get().Get(), device);
        if (FAILED(hr))
        {
            std::cout << "Failed to create Direct2D device" << std::endl;
            exit(1);
        }
    }
};

}  // namespace karin

#endif  // KARIN_WINDOWS_DIRECT2D_D2DDEVICE_H

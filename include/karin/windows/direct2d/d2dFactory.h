#ifndef KARIN_WINDOWS_DIRECT2D_D2DFACTORY_H
#define KARIN_WINDOWS_DIRECT2D_D2DFACTORY_H

#include <d2d1_1.h>
#include <wrl.h>

#include <iostream>

namespace karin
{

class d2dFactory
{
public:
    static Microsoft::WRL::ComPtr<ID2D1Factory1>& Get()
    {
        static Microsoft::WRL::ComPtr<ID2D1Factory1> factory = nullptr;
        if (factory == nullptr)
        {
            const HRESULT hr = D2D1CreateFactory(
                D2D1_FACTORY_TYPE_MULTI_THREADED,
                __uuidof(ID2D1Factory1),
                &factory
            );
            if (FAILED(hr))
            {
                std::cout << "Failed to create Direct2D factory" << std::endl;
                exit(1);
            }
        }

        return factory;
    }
};

}  // namespace karin

#endif  // KARIN_WINDOWS_DIRECT2D_D2DFACTORY_H

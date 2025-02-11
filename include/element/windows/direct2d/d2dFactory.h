#ifndef ELEMENT_WINDOWS_DIRECT2D_D2DFACTORY_H
#define ELEMENT_WINDOWS_DIRECT2D_D2DFACTORY_H

#include <d2d1_3.h>
#include <wrl.h>

#include <iostream>

namespace element
{

class d2dFactory
{
public:
    static Microsoft::WRL::ComPtr<ID2D1Factory8>& Get()
    {
        static Microsoft::WRL::ComPtr<ID2D1Factory8> factory = nullptr;
        if (factory == nullptr)
        {
            HRESULT hr = D2D1CreateFactory(
                D2D1_FACTORY_TYPE_MULTI_THREADED,
                __uuidof(ID2D1Factory8),
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

}  // namespace element

#endif  // ELEMENT_WINDOWS_DIRECT2D_D2DFACTORY_H

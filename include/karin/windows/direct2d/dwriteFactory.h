#ifndef KARIN_WINDOWS_DIRECT2D_DWRITEFACTORY_H
#define KARIN_WINDOWS_DIRECT2D_DWRITEFACTORY_H
#include <dwrite.h>
#include <wrl/client.h>

#include <iostream>

namespace karin
{

class dwriteFactory
{
public:
    static Microsoft::WRL::ComPtr<IDWriteFactory>& Get()
    {
        static Microsoft::WRL::ComPtr<IDWriteFactory> factory = nullptr;
        if (factory == nullptr)
        {
            const HRESULT hr = DWriteCreateFactory(
                DWRITE_FACTORY_TYPE_SHARED,
                __uuidof(IDWriteFactory),
                &factory
            );
            if (FAILED(hr))
            {
                std::cout << "Failed to create DirectWrite factory"
                          << std::endl;
                exit(1);
            }
        }

        return factory;
    }
};

}  // namespace karin

#endif  // KARIN_WINDOWS_DIRECT2D_DWRITEFACTORY_H

#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#include <Windows.h>

namespace element
{

class winWindow
{
public:
    winWindow() = default;
    winWindow(const winWindow&) = delete;
    winWindow& operator=(const winWindow&) = delete;
    winWindow(winWindow&&) = delete;
    winWindow& operator=(winWindow&&) = delete;
    ~winWindow();

    HRESULT Create(
        const wchar_t* title = L"",
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int width = CW_USEDEFAULT,
        int height = CW_USEDEFAULT
    );
    [[nodiscard]] bool IsActive() const;
    [[nodiscard]] bool IsShow() const;
    [[nodiscard]] HWND GetHwnd() const;
    void Destroy();
    void Show();
    void Run();
    void Hide();

    static LRESULT CALLBACK
    WinWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        winWindow* pThis = nullptr;

        if (uMsg == WM_CREATE)
        {
            auto* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<winWindow*>(pCreate->lpCreateParams);
            SetWindowLongPtr(
                hwnd,
                GWLP_USERDATA,
                reinterpret_cast<LONG_PTR>(pThis)
            );

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = reinterpret_cast<winWindow*>(
                GetWindowLongPtr(hwnd, GWLP_USERDATA)
            );
        }

        if (pThis != nullptr)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

private:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND m_hwnd{nullptr};
    bool m_isShow{false};
};

}  // namespace element

#endif  // WIN_WINDOW_H

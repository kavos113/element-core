#ifndef ELEMENT_WINDOWS_WIN_WINDOWS_H
#define ELEMENT_WINDOWS_WIN_WINDOWS_H

#ifndef UNICODE
#define UNICODE
#include <geometry/Rectangle.h>
#include <geometry/Size.h>

#include "color/Color.h"
#include "direct2d/d2dWindow.h"
#endif

#include <Windows.h>

#include <thread>

namespace element
{

class winWindow
{
public:
    enum class ShowStatus
    {
        HIDE,
        SHOW,
        MINIMIZE,
        MAXIMIZE
    };

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
    [[nodiscard]] ShowStatus GetShowStatus() const;
    [[nodiscard]] HWND GetHwnd() const;

    void Show();
    void Run();
    void Hide();
    void Minimize();
    void Maximize();

    [[nodiscard]] Size GetSize() const;
    void SetSize(Size size);
    [[nodiscard]] Point GetPosition() const;
    void SetPosition(Point position);
    [[nodiscard]] Rectangle GetRectangle() const;
    void SetRectangle(Rectangle rect);
    [[nodiscard]] Color GetBackgroundColor() const;
    void SetBackgroundColor(Color color);

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
    ShowStatus m_showStatus{ShowStatus::HIDE};
    d2dWindow m_d2dWindow{};

    Rectangle m_rect{};
    Color m_backgroundColor{Color::Colors::White};
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_WIN_WINDOWS_H

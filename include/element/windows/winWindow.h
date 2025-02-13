#ifndef ELEMENT_WINDOWS_WIN_WINDOWS_H
#define ELEMENT_WINDOWS_WIN_WINDOWS_H

#ifndef UNICODE
#define UNICODE
#endif

#include <geometry/Rectangle.h>
#include <geometry/Size.h>
#include <Windows.h>

#include <thread>

#include "color/Color.h"
#include "direct2d/d2dWindow.h"

#define WM_ELEMENT_INVOKE          0x401
#define WM_ELEMENT_GETSTATUS       0x402

#define EL_WINDOW_SHOW             1
#define EL_WINDOW_HIDE             2
#define EL_WINDOW_MINIMIZE         3
#define EL_WINDOW_MAXIMIZE         4
#define EL_WINDOW_SIZE             5
#define EL_WINDOW_POSITION         6
#define EL_WINDOW_RECTANGLE        7
#define EL_WINDOW_BACKGROUND_COLOR 8
#define EL_WINDOW_ACTIVE           9
#define EL_WINDOW_SHOWSTATUS       10
#define EL_WINDOW_HWND             11

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

    static HRESULT RegisterWindowClass();
    static HRESULT UnregisterWindowClass();
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
    WinWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    void Invoke(WPARAM wParam, LPARAM lParam);
    void GetStatus(WPARAM wParam, LPARAM lParam) const;

    HWND m_hwnd{nullptr};
    ShowStatus m_showStatus{ShowStatus::HIDE};
    d2dWindow m_d2dWindow{};

    Rectangle m_rect{};
    Color m_backgroundColor{Color::Colors::White};

    static constexpr const wchar_t* CLASS_NAME = L"element_window";
};

}  // namespace element

#endif  // ELEMENT_WINDOWS_WIN_WINDOWS_H

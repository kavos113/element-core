#ifndef KARIN_X11_X11WINDOW_H
#define KARIN_X11_X11WINDOW_H

#include <X11/Xlib.h>

#include <cstdint>

#include "geometry/Rectangle.h"

namespace karin
{

class x11Window
{
public:
    enum class ShowStatus : uint8_t
    {
        HIDE,
        SHOW,
        MINIMIZE,
        MAXIMIZE
    };

    x11Window() = default;
    x11Window(const x11Window&) = delete;
    x11Window& operator=(const x11Window&) = delete;
    x11Window(x11Window&&) = delete;
    x11Window& operator=(x11Window&&) = delete;
    ~x11Window();

    bool Create(
        const char* title = "",
        int x = 0,
        int y = 0,
        int width = 800,
        int height = 600
    );
    [[nodiscard]] bool IsActive() const;

    void Show();
    void Run();
    void Hide();
    void Maximize();
    void Minimize();

    void SetSize(const Size size);
    Size GetSize() const;
    void SetPosition(const Point position);
    Point GetPosition() const;
    void SetRectangle(const Rectangle rect);
    Rectangle GetRectangle() const;

    Window GetWindow() const;
    Display* GetDisplay() const;
    ShowStatus GetShowStatus() const;

private:
    Display* m_display = nullptr;
    Window m_window = 0;
    GC gc = 0;

    ShowStatus m_showStatus = ShowStatus::HIDE;
    Rectangle m_rect;

    bool m_isStarted = false;
};

}  // namespace karin

#endif  // KARIN_X11_X11WINDOW_H

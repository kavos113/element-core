#ifndef KARIN_X11_X11WINDOW_H
#define KARIN_X11_X11WINDOW_H

#include <X11/Xlib.h>

namespace karin
{

class x11Window
{
public:
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

    Window GetWindow() const
    {
        return m_window;
    }

    Display* GetDisplay() const
    {
        return m_display;
    }

private:
    Display* m_display = nullptr;
    Window m_window = 0;
    GC gc = 0;
};

}  // namespace karin

#endif  // KARIN_X11_X11WINDOW_H

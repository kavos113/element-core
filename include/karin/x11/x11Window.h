#ifndef KARIN_X11_X11WINDOW_H
#define KARIN_X11_X11WINDOW_H

#include <X11/Xlib.h>

#include <cstdint>

#include "color/Color.h"
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
        int width = DEFAULT_WIDTH,
        int height = DEFAULT_HEIGHT
    );
    [[nodiscard]] bool IsActive() const;

    void Show();
    void Run();
    void Hide();
    void Maximize();
    void Minimize();

    void SetSize(Size size);
    [[nodiscard]] Size GetSize() const;
    void SetPosition(Point position);
    [[nodiscard]] Point GetPosition() const;
    void SetRectangle(Rectangle rect);
    [[nodiscard]] Rectangle GetRectangle() const;
    void SetBackgroundColor(Color color);
    [[nodiscard]] Color GetBackgroundColor() const;

    [[nodiscard]] Window GetWindow() const;
    [[nodiscard]] Display* GetDisplay() const;
    [[nodiscard]] ShowStatus GetShowStatus() const;

private:
    Display* m_display = nullptr;
    Window m_window = 0;
    GC gc = nullptr;

    ShowStatus m_showStatus = ShowStatus::HIDE;
    Rectangle m_rect{};

    Color m_backgroundColor = Color(1.0f, 1.0f, 1.0f, 1.0f);

    bool m_isStarted = false;

    static constexpr int XCLIENT_FORMAT = 32;
    static constexpr int DEFAULT_WIDTH = 800;
    static constexpr int DEFAULT_HEIGHT = 600;
};

}  // namespace karin

#endif  // KARIN_X11_X11WINDOW_H

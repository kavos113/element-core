#include "x11/x11Window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>

namespace karin
{

x11Window::~x11Window()
{
    if (gc != nullptr)
    {
        XFreeGC(m_display, gc);
    }
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
}

bool x11Window::Create(const char *title, int x, int y, int width, int height)
{
    XSizeHints *size_hints = XAllocSizeHints();
    if (size_hints == nullptr)
    {
        std::cerr << "couldn't allocate size hints" << std::endl;
        return false;
    }

    XWMHints *wm_hints = XAllocWMHints();
    if (wm_hints == nullptr)
    {
        std::cerr << "couldn't allocate WM hints" << std::endl;
        return false;
    }

    XClassHint *class_hints = XAllocClassHint();
    if (class_hints == nullptr)
    {
        std::cerr << "couldn't allocate class hints" << std::endl;
        return false;
    }

    m_display = XOpenDisplay(nullptr);
    if (m_display == nullptr)
    {
        std::cerr << "couldn't open display" << std::endl;
        return false;
    }

    int screen_num = DefaultScreen(m_display);

    m_window = XCreateSimpleWindow(
        m_display,
        RootWindow(m_display, screen_num),
        x,
        y,
        width,
        height,
        4,
        BlackPixel(m_display, screen_num),
        WhitePixel(m_display, screen_num)
    );

    size_hints->flags = PPosition | PSize;

    XTextProperty window_name;
    Status status = XStringListToTextProperty(
        const_cast<char **>(&title),
        1,
        &window_name
    );
    if (status == 0)
    {
        std::cerr << "couldn't create window name string" << std::endl;
        return false;
    }

    wm_hints->flags = InputHint | StateHint;
    wm_hints->input = True;
    wm_hints->initial_state = NormalState;

    class_hints->res_name = const_cast<char *>(title);
    class_hints->res_class = const_cast<char *>(title);

    XSetWMProperties(
        m_display,
        m_window,
        &window_name,
        nullptr,
        nullptr,
        0,
        size_hints,
        wm_hints,
        class_hints
    );

    XSelectInput(m_display, m_window, ExposureMask | StructureNotifyMask);

    unsigned long valuemask = 0;
    XGCValues values;
    gc = XCreateGC(m_display, m_window, valuemask, &values);

    return true;
}

bool x11Window::IsActive() const
{
    return m_window != 0;
}

void x11Window::Show()
{
    if (m_window == 0)
    {
        return;
    }

    XMapWindow(m_display, m_window);

    m_showStatus = ShowStatus::SHOW;
}

void x11Window::Run()
{
    XEvent event;

    while (true)
    {
        XNextEvent(m_display, &event);

        switch (event.type)
        {
            case ClientMessage:
                m_showStatus = ShowStatus::HIDE;
                return;

            default:
                break;
        }
    }
}

Window x11Window::GetWindow() const
{
    return m_window;
}

Display *x11Window::GetDisplay() const
{
    return m_display;
}

x11Window::ShowStatus x11Window::GetShowStatus() const
{
    return m_showStatus;
}

}  // namespace karin
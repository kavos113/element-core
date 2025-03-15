#include "x11/x11Window.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>
#include <thread>

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

    if (m_isStarted)
    {
        XMapWindow(m_display, m_window);
    }

    m_showStatus = ShowStatus::SHOW;
}

void x11Window::Run()
{
    if (m_showStatus != ShowStatus::HIDE)
    {
        XMapWindow(m_display, m_window);
    }

    XEvent event;

    m_isStarted = true;

    while (true)
    {
        XNextEvent(m_display, &event);

        // std::cout << "Event type: " << event.type << std::endl;

        switch (event.type)
        {
            case ClientMessage:
            {
                const Atom delete_window
                    = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
                if (delete_window == event.xclient.data.l[0])
                {
                    m_showStatus = ShowStatus::HIDE;
                    return;
                }
            }
            break;

            case Expose:
                switch (m_showStatus)
                {
                    case ShowStatus::MAXIMIZE:
                        Maximize();
                        break;

                    case ShowStatus::MINIMIZE:
                        Minimize();
                        break;
                }
                break;

            default:
                break;
        }
    }
}

void x11Window::Hide()
{
    if (m_window == 0)
    {
        return;
    }

    if (m_isStarted)
    {
        XUnmapWindow(m_display, m_window);
    }

    m_showStatus = ShowStatus::HIDE;
}

void x11Window::Maximize()
{
    m_showStatus = ShowStatus::MAXIMIZE;

    if (!m_isStarted)
    {
        return;
    }

    XEvent event = {};

    event.type = ClientMessage;
    event.xclient.window = m_window;
    event.xclient.message_type = XInternAtom(m_display, "_NET_WM_STATE", False);
    event.xclient.format = 32;
    event.xclient.data.l[0] = 1;  // _NET_WM_STATE_ADD
    event.xclient.data.l[1]
        = XInternAtom(m_display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    event.xclient.data.l[2]
        = XInternAtom(m_display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    event.xclient.data.l[3] = 0;

    XSendEvent(
        m_display,
        DefaultRootWindow(m_display),
        False,
        SubstructureRedirectMask | SubstructureNotifyMask,
        &event
    );

    XFlush(m_display);
}

void x11Window::Minimize()
{
    m_showStatus = ShowStatus::MINIMIZE;

    if (!m_isStarted)
    {
        return;
    }

    XIconifyWindow(m_display, m_window, DefaultScreen(m_display));

    XFlush(m_display);
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
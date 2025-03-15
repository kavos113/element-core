#ifndef TEST_UTILS_X11GUITESTER_H
#define TEST_UTILS_X11GUITESTER_H

#include <X11/Xlib.h>

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

#include "x11/x11Window.h"

class X11GUITester
{
public:
    X11GUITester() = default;

    void RegisterWindow(const karin::x11Window& window)
    {
        m_targetWindow = window.GetWindow();
        m_display = window.GetDisplay();
    }

    void CloseWindow()
    {
        m_actions.emplace_back(
            [this]
            {
                const Atom closeEvent
                    = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
                if (closeEvent == XAtom_None)
                {
                    return;
                }

                XEvent event = {};
                event.type = ClientMessage;
                event.xclient.window = m_targetWindow;
                event.xclient.message_type = closeEvent;
                event.xclient.format = XCLIENT_FORMAT;
                event.xclient.data.l[0] = static_cast<int32_t>(closeEvent);

                const Status status = XSendEvent(
                    m_display,
                    m_targetWindow,
                    False,
                    NoEventMask,
                    &event
                );
                if (status == 0)
                {
                    return;
                }
                XFlush(m_display);
            }
        );
    }

    void Run(const bool isPause = false) const
    {
        std::this_thread::sleep_for(INIT_INTERVAL);
        for (const auto& action : m_actions)
        {
            action();
            if (isPause)
            {
                std::this_thread::sleep_for(INTERVAL);
            }
        }
    }

private:
    static constexpr auto INIT_INTERVAL = std::chrono::milliseconds(500);
    static constexpr auto INTERVAL = std::chrono::milliseconds(200);

    static constexpr uint64_t XAtom_None = 0;
    static constexpr int XCLIENT_FORMAT = 32;

    std::vector<std::function<void()>> m_actions;
    Display* m_display{nullptr};
    Window m_targetWindow{0};
};

#endif  // TEST_UTILS_X11GUITESTER_H

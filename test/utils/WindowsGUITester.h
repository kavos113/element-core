#ifndef WINDOWSGUITESTER_H
#define WINDOWSGUITESTER_H

#include <Windows.h>
#include <windows/winWindow.h>

#include <chrono>
#include <thread>

class WindowsGUITester
{
public:
    void RegisterWindow(const element::winWindow& window)
    {
        m_targetHwnd = window.GetHwnd();
    }

    void AddAction(
        const std::chrono::duration<int, std::milli> delay,
        const UINT message,
        const WPARAM wParam,
        const LPARAM lParam,
        const std::function<void()>& assertion = nullptr
    )
    {
        m_actions.push_back(
            {.delay = delay,
             .message = message,
             .wParam = wParam,
             .lParam = lParam,
             .assertion = assertion}
        );
    }

    void Run()
    {
        for (const auto& [delay, message, wParam, lParam, assertion] :
             m_actions)
        {
            std::this_thread::sleep_for(delay);
            PostMessage(m_targetHwnd, message, wParam, lParam);
            if (assertion)
            {
                assertion();
            }
        }
    }

    std::future<void> RunAsync()
    {
        return std::async(
            std::launch::async,
            [this]()
            {
                for (const auto& [delay, message, wParam, lParam, assertion] :
                     m_actions)
                {
                    std::this_thread::sleep_for(delay);
                    if (assertion)
                    {
                        assertion();
                    }
                    PostMessage(m_targetHwnd, message, wParam, lParam);
                }
            }
        );
    }

private:
    struct Action
    {
        std::chrono::duration<int, std::milli> delay;
        UINT message;
        WPARAM wParam;
        LPARAM lParam;
        std::function<void()> assertion;
    };

    std::vector<Action> m_actions;
    HWND m_targetHwnd = nullptr;
};

#endif  // WINDOWSGUITESTER_H

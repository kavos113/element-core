#ifndef TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H
#define TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H

#include <Windows.h>
#include <windows/winWindow.h>

#include <chrono>
#include <thread>

class WindowsGUITester
{
public:
    WindowsGUITester()
    {
    }

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
             .action = [this, message, wParam, lParam]
             { SendMessage(m_targetHwnd, message, wParam, lParam); },
             .assertion = assertion}
        );
    }

    void AddAction(
        const std::chrono::duration<int, std::milli> delay,
        const std::function<void()>& action,
        const std::function<void()>& assertion = nullptr
    )
    {
        m_actions.push_back(
            {.delay = delay, .action = action, .assertion = assertion}
        );
    }

    void Run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(INIT_INTERVAL));
        int i = 0;
        for (const auto& [delay, action, assertion] : m_actions)
        {
            i++;
            action();
            std::this_thread::sleep_for(delay);
            if (assertion)
            {
                assertion();
            }
        }
    }

    std::future<void> RunAsync()
    {
        return std::async(std::launch::async, [this]() { Run(); });
    }

private:
    struct Action
    {
        std::chrono::duration<int, std::milli> delay;
        std::function<void()> action;
        std::function<void()> assertion;
    };

    static constexpr int INIT_INTERVAL = 1000;

    std::vector<Action> m_actions;
    HWND m_targetHwnd = nullptr;
};

#endif  // TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H

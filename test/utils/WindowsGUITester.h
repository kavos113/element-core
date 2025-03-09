#ifndef TEST_UTILS_WINDOWSGUITESTER_H
#define TEST_UTILS_WINDOWSGUITESTER_H

#include <Windows.h>
#include <windows/winWindow.h>

#include <chrono>
#include <functional>
#include <thread>
#include <vector>

class WindowsGUITester
{
public:
    WindowsGUITester() = default;

    void RegisterWindow(const karin::winWindow& window)
    {
        m_targetHwnd = std::make_unique<HWND>(window.GetHwnd());
    }

    void AddAction(
        const std::function<void()>& action,
        const std::function<void()>& assertion
    )
    {
        m_actions.push_back({.action = action, .assertion = assertion});
    }

    void CloseWindow()
    {
        m_actions.push_back(
            {.action = [this] { SendMessage(*m_targetHwnd, WM_CLOSE, 0, 0); },
             .assertion = [] {}}
        );
    }

    void Run(const bool is_pause = false)
    {
        std::this_thread::sleep_for(INIT_INTERVAL);
        for (const auto& [action, assertion] : m_actions)
        {
            action();
            if (is_pause)
            {
                std::this_thread::sleep_for(INTERVAL);
            }

            assertion();
        }
    }

private:
    struct Action
    {
        std::function<void()> action;
        std::function<void()> assertion;
    };

    static constexpr auto INIT_INTERVAL = std::chrono::milliseconds(200);
    static constexpr auto INTERVAL = std::chrono::milliseconds(200);

    std::vector<Action> m_actions;
    std::unique_ptr<HWND> m_targetHwnd;
};

#endif  // TEST_UTILS_WINDOWSGUITESTER_H

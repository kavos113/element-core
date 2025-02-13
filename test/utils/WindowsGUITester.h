#ifndef TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H
#define TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H

#include <Windows.h>
#include <windows/winWindow.h>

#include <chrono>
#include <thread>

class WindowsGUITester
{
public:
    enum class Assertions
    {
        EQUAL,
        NOT_EQUAL,
        NONE,
    };

    WindowsGUITester() = default;

    void RegisterWindow(const element::winWindow& window)
    {
        m_targetHwnd = std::make_unique<HWND>(window.GetHwnd());
    }

    template<typename T>
    void AddAction(
        const WPARAM wParam,
        const LPARAM lParam,
        const Assertions assertion_type,
        const WPARAM assertion_wParam,
        const T& expected
    )
    {
        m_actions.push_back(
            {.action = {WM_ELEMENT_INVOKE, wParam, lParam},
             .assertion =
                 [this, expected, assertion_wParam, assertion_type]()
             {
                 if (assertion_type == Assertions::NONE)
                 {
                     return;
                 }

                 T actual = {};
                 SendMessage(
                     *m_targetHwnd,
                     WM_ELEMENT_GETSTATUS,
                     assertion_wParam,
                     reinterpret_cast<LPARAM>(&actual)
                 );
                 switch (assertion_type)
                 {
                     case Assertions::EQUAL:
                         ASSERT_EQ(expected, actual);
                         break;

                     case Assertions::NOT_EQUAL:
                         ASSERT_NE(expected, actual);
                         break;

                     default:
                         break;
                 }
             }}
        );
    }

    void CloseWindow()
    {
        m_actions.push_back({{WM_CLOSE, 0, 0}, []() {}});
    }

    void Run(bool is_pause = false)
    {
        std::this_thread::sleep_for(INIT_INTERVAL);
        int i = 0;
        for (const auto& [action, assertion] : m_actions)
        {
            i++;
            SendMessage(
                *m_targetHwnd,
                action.message,
                action.wParam,
                action.lParam
            );
            if (is_pause)
            {
                std::this_thread::sleep_for(INTERVAL);
            }

            assertion();
        }
    }

    std::future<void> RunAsync()
    {
        return std::async(std::launch::async, [this]() { Run(); });
    }

private:
    struct ActionFunction
    {
        UINT message;
        WPARAM wParam;
        LPARAM lParam;
    };

    struct Action
    {
        ActionFunction action;
        std::function<void()> assertion;
    };

    static constexpr std::chrono::milliseconds INIT_INTERVAL
        = std::chrono::milliseconds(500);
    static constexpr std::chrono::milliseconds INTERVAL
        = std::chrono::milliseconds(200);

    std::vector<Action> m_actions;
    std::unique_ptr<HWND> m_targetHwnd;
};

#endif  // TEST_ELEMENT_UTILS_WINDOWSGUITESTER_H

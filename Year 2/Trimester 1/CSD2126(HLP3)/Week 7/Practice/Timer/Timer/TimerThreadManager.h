#pragma once

#include <thread>
#include <atomic>

class TimerThreadManager 
{
public:
    TimerThreadManager();
    ~TimerThreadManager();

    void StartTimerThread();
    void StopTimerThread();
    std::atomic<bool> timerRunning;

private:
    std::thread timerThread;

    void TimerFunction();
};

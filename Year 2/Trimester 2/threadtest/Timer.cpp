#include "Timer.h"
#include <iostream>
#include <chrono>
#include <functional>
#include <future>

// Static member function to be executed by the timer thread
void BackgroundTimer::timerThread(BackgroundTimer *timer)
{
    while (timer->running_)
    {
        timer->callback_();
    }
}

BackgroundTimer::BackgroundTimer(int interval, std::function<void()> callback)
    : interval_(interval), callback_(std::move(callback)), running_(false) {}

void BackgroundTimer::start()
{
    if (!running_)
    {
        running_ = true;
        thread_ = std::thread([this]() { timerThread(this); });
    }
}

void BackgroundTimer::stop()
{
    if (running_)
    {
        running_ = false;
        if (thread_.joinable())
        {
            thread_.join();
        }
    }
}

BackgroundTimer::~BackgroundTimer()
{
    stop();
}

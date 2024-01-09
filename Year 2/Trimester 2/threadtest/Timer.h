#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <thread>

class BackgroundTimer {
public:
    void timerThread(BackgroundTimer *timer);
    BackgroundTimer(int interval, std::function<void()> callback);
    void start();
    void stop();
    ~BackgroundTimer();

    bool GetRunning() {return running_;}
private:
    int interval_;
    std::function<void()> callback_;
    std::thread thread_;
    bool running_;
};

#endif // TIMER_H
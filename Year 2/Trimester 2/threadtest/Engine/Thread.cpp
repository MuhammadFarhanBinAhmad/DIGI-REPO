#include "Thread.h"

testThread::~testThread()
{
    joinThread();
}
testThread::testThread(void (*func)(), int time) 
{
    timerThread = std::thread([this, func, time]() 
    {
        std::this_thread::sleep_for(std::chrono::seconds(time));
        func();  // Call the member function within the lambda
    });
    timerThread.detach();  // Detach the thread so it can run independently
}
void testThread::joinThread() 
{
    if (timerThread.joinable()) {
        timerThread.join();
    }
}
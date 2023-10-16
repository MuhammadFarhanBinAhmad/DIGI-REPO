#include "TimerThreadManager.h"
#include <iostream>
#include <chrono>

TimerThreadManager::TimerThreadManager() : timerRunning(true) {}

TimerThreadManager::~TimerThreadManager() 
{
    StopTimerThread();
}

void TimerThreadManager::StartTimerThread() 
{
    timerThread = std::thread(&TimerThreadManager::TimerFunction, this);
}

void TimerThreadManager::StopTimerThread() 
{
    timerRunning = false; // Signal the timer thread to exit
    if (timerThread.joinable()) 
    {
        timerThread.join(); // Wait for the timer thread to finish
    }
}

void TimerThreadManager::TimerFunction() 
{
    std::cout << "START TIMER\n";
    int counter = 0;
    while (timerRunning) 
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Perform any timer-related tasks here
        std::cout << "Timer Tick " << counter << '\n';
        counter++;

        // You can add additional exit conditions here
        if (counter >= 5) 
        {
            timerRunning = false;
            break;
        }
    }
}

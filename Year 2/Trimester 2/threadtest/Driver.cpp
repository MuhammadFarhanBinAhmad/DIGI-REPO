#include "Timer.h"
#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Example function to be called by the timer
void PrintCallback()
{
    for(int i = 0;i < 50;i++)
    {
        std::cout << "Thread check\n";
    }
}

void TimerCallBack(std::promise<void>& localPromise) {
    // Simulate a delay without blocking the thread
    auto startTime = std::chrono::high_resolution_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - startTime).count() < 3) {
        // Do nothing, just wait for 3 seconds
    }
    std::cout << "TIMER ENDED\n";
    localPromise.set_value(); // Notify that the timer has ended
}

void RunEngine()
{
    std::cout << "Engine Running\n";
}
//seems to be working. Need more case test
int main()
{
    while(true)
    {
        //RunEngine();
        // BackgroundTimer timer(5000, TimerCallBack); // Timer with a 1-second interval
        // // Start the timer in the background
        // timer.start();

        // // Main program continues running
        // // for (int i = 0; i < 3; ++i)
        // // {
        // //     std::this_thread::sleep_for(std::chrono::seconds(1));
        // //     std::cout << "Main program is still running..." << std::endl;
        // // }

        // // // Stop the timer when no longer needed
        // timer.stop();

        // BackgroundTimer timer2(1000, PrintCallback); // Timer with a 1-second interval
        // timer2.start();
        // // for (int i = 0; i < 3; ++i)
        // // {
        // //     std::this_thread::sleep_for(std::chrono::seconds(1));
        // //     std::cout << "Main program 2 is still running..." << std::endl;
        // // }
        // timer2.stop();

        RunEngine();

        // Use std::thread to launch the timer function concurrently
        std::promise<void> promise;
        auto future = promise.get_future();
        std::thread timerThread(&TimerCallBack, std::ref(promise));

        // Perform other tasks concurrently with the timer thread
        // ...

        // Join the timer thread to wait for its completion
        timerThread.join();

        // Check if the timer has completed
        if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
            std::cout << "Timer completed.\n";
        } else {
            std::cout << "Timer still running.\n";
        }
    }

    return 0;
}

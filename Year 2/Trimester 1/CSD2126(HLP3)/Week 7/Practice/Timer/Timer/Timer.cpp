#include "TimerThreadManager.h"
#include "AnotherFile.h"
#include <iostream>
#include <chrono>

int main() {

    //TimerThreadManager timerManager;

    //timerManager.StartTimerThread();
    //AnotherFunction();
    std::thread anotherThread(AnotherFunction);

    while (true) 
    {
        // Your main program logic
        std::cout << "Main thread: Other work...\n";

        // You can continue to run other code in the main thread
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Check for an exit condition and stop the timer thread if needed
        /*if (!timerManager.timerRunning)
        {
           break;
        }*/
    }
    anotherThread.join();
    //timerManager.StopTimerThread();

    return 0;
}

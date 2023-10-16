#include "TimerThreadManager.h"
#include "AnotherFile.h"
#include <iostream>

void AnotherFunction() 
{
	TimerThreadManager timerManager;
	timerManager.StartTimerThread();
	while (true)
	{
        // Your main program logic
        std::cout << "Another thread: Other work...\n";

        // You can continue to run other code in the main thread
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Check for an exit condition and stop the timer thread if needed
       if (!timerManager.timerRunning)
        {
           break;
        }
	}
}

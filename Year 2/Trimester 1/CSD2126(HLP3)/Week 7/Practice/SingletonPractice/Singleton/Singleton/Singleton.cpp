// Random.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "Singleton.h"
//SINGLETON CLASS
// Function to run the timer in the background
void BackgroundTimer() {
    int seconds = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        seconds++;

        // Print the elapsed time (you can replace this with your desired action)
        std::cout << "Elapsed time: " << seconds << " seconds" << std::endl;
    }
}
int main()
{

    float number = Random::Float();

    std::cout << number << std::endl;

    // Start the background timer in a separate thread
    std::thread timerThread(BackgroundTimer);

    // Allow the main thread to run other processes
    while (true) 
    {
        // Replace this loop with your application's main logic
        // Other processes can run concurrently with the timer
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate other work
    }
    std::cout << number << std::endl;


    return 0;
}

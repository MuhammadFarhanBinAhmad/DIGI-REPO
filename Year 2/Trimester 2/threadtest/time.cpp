#include <iostream>
#include <ctime>
#include <string>
#include <tuple>
#include <utility>

using namespace std;

template<typename... Args>
void StartTimer(short endTime, void (*func)(Args...), Args&&... args) {
    time_t initialTime = time(0);
    time_t currentTime;
    bool timerEnd = false;

    while (!timerEnd) 
    {
        currentTime = time(0);
        if (difftime(currentTime, initialTime) >= endTime) {
            timerEnd = true;
        }
    }
    func(std::forward<Args>(args)...);
}

template<typename... Args>
bool StartTimerbool(short endTime, void (*func)(Args...), Args&&... args) {
    time_t initialTime = time(0);
    time_t currentTime;
    bool timerEnd = false;

    while (!timerEnd) 
    {
        currentTime = time(0);
        if (difftime(currentTime, initialTime) >= endTime) {
            timerEnd = true;
        }
    }
    func(std::forward<Args>(args)...);
    return true;
}
void print()
{
    std::cout << "NULL\n";
}
void printint(int i) {
    std::cout << i << " \n";
}

void printfloat(float f) {
    std::cout << f << " \n";
}

void printstring(std::string s) {
    std::cout << s << " \n";
}

void printfloatstring(float f, std::string s) {
    std::cout << f << " \n";
    std::cout << s << " \n";
}

void printstringint(std::string s, int i) {
    std::cout << s << " \n";
    std::cout << i << " \n";
}

void printall(int i, float f, std::string s) {
    std::cout << s << " \n";
    std::cout << i << " \n";
    std::cout << f << " \n";
}

int main() {
    StartTimer(5,print);
    // StartTimer<int>(5, printint, 42);
    // StartTimer<float>(5, printfloat, 42.5f);
    // StartTimer<std::string>(5, printstring, "Cat");
    // StartTimer<float, std::string>(5, printfloatstring, 42.5f, "Dog");
    // StartTimer<std::string, int>(5, printstringint, "Bird", 42);
    StartTimer<int, float, std::string>(5, printall, 42, 42.5f, "Fish");

    // while(StartTimerbool(3,print))
    // {
    //     std::cout << "hit\n";
    // }
    // int time_delay;

    // cout << "Enter the time for which you want to make a delay in the output: " << flush;
    // cin >> time_delay;

    // time_delay *= CLOCKS_PER_SEC;
    // clock_t now = clock();

    // while (clock() - now < time_delay);
    // cout << " The message Show after delay as per your entered time. " << endl;
    // return 0;
}

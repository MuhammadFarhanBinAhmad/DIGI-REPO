#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>

class testThread 
{
private:
    std::thread timerThread;

public:
    bool exitFlag = false;
    testThread(void (*func)(),int time);
    testThread(void (*func)(testThread&,int), int time);
    testThread(void (*func)(testThread&,std::string), std::string);
    ~testThread();
    void joinThread();
};
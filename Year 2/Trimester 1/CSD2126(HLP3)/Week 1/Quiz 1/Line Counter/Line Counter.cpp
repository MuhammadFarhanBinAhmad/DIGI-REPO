// Line Counter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "lines.hpp"
int main()
{
    const char* test[] = { "test.txt","test1.txt",nullptr};
    lines(test);
}

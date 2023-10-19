// PolyTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "polynomial.h"

int main() 
{
    HLP3::Polynomial<int, 3> p3;
    p3[0] = 1;
    p3[1] = 1;
    p3[2] = 1;
    p3[3] = 1; // defines 1+x+x^2+x^3

    HLP3::Polynomial<float, 2> pf_1;
    pf_1[0] = 1.1;
    pf_1[1] = -2.2;
    pf_1[2] = 1.1;
    std::cout << pf_1 << std::endl;

    // multiplcation of 2 different types of coefficients 
    // should NOT compile
    pf_1* p3;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

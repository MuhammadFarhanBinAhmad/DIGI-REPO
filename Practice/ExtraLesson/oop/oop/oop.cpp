// oop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>


class MyInt
{
public :
    //RULE OF 3
    MyInt()
    : ptr{new int()}
    {
        //ptr = new int();//bracket will auto 0 it
    }
    MyInt(const MyInt& rhs)//Copy Assignment
        : ptr{ new int {*(rhs.ptr)}}
    {

    }
    MyInt& operator= (const MyInt& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        *ptr = *rhs.ptr;
        return *this;
    }
    ~MyInt()
    {
        delete ptr;
    }

    int* ptr;
};

int main()
{
    MyInt a;
    MyInt b = a;//if no copy construcot = will crash cause delete twice
    MyInt c;
    c = a;//copy assignment

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

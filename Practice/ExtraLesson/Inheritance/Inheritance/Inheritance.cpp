// Inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Shape
{
public :
    uint32_t color;
    float multiplier;

    float GetArea() const
    {
        return 0 * 0;
    }
};
class Rectangle : public Shape
{
public:
    float width;
    float height;

    float GetArea()
    {
        return width * height;
    }
};
class  Circle : public Shape
{
public:
    float radius;

    float GetArea()
    {
        return 3.142 * radius * radius;
    }
private:

};

int main()
{
    std::cout << "Hello World!\n";
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

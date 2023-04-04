// Iterators.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <map>

std::vector<int> foo(std::istream& is) {
    std::vector<int> ret;
    int value;
    while (is >> value) {
        ret.push_back(value);
    }
    return ret;
}
template<typename T>
void print(std::vector<T>& const cont)
{
    typename std::vector<T>::iterator ptr;

    for (ptr = cont.begin(); ptr < cont.end(); ptr++)
    {
        std::cout << *ptr << std::endl;
    }
}
int main()
{
    std::string filename = "1 2 3 4 5 6";
    std::istringstream st(filename);

    std::vector<int> a = foo(st);

    print(a);


}

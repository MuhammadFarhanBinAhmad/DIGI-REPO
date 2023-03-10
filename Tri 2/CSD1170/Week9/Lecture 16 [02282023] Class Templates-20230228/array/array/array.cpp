// array.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>

//return size of array during compile time
template <typename T,size_t N>
constexpr size_t arr_len(T const(&)[N])
{
    return N;
}

//try to do as much as possible in compile time

int main()
{
    size_t constexpr arr_sz{ 5 };//legal cause const
    std::array<int, arr_sz> ai{ 1,2,3,4,5 };

    size_t value;
    std::cin >> value;
    //size_t constexpr arr_sz2{ value };
    //std::array<int, arr_sz2>ai{};//not legal cause value variable is know at run time

    size_t constexpr arr_sz2{ 5 };//constexpr enable variable to be known during compile time not runtime
    std::array<int, arr_sz2>ai{10,20};//thus why this works. cause array need to know the value during compile

    int ai2[]{ 3,4,5,6,7,8 };
    int ai3[arr_len(ai2)];
}


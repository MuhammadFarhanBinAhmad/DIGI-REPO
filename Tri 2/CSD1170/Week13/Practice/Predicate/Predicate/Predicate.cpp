// Predicate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
//isOdd is a functor
struct isOdd
{
    bool operator()(int x) { return x % 2; }
};

struct point
{
    double x{}, y{};
    point(double dx = 0., double dy = 0.) :x{ dx }, y{ dy }{}
    double dist2() const { return x * x + y * y; }
};
bool operator<(point const& a, point const& b) {return a.dist2() < b.dist2(); }



bool isEven(int a) { return !(a % 2); }
bool isEqual(int a, int b) { return a == b; }
int main()
{
    std::vector<int> col1{ 1,2,3,4,5,6,7,8,9,10,11 };
    std::vector<point> v1{ {0.6, 4.1}, {-2, 1.9}, {1.1, -1.1}, {0, 2.1}, {-1, 2.2} };
    std::vector<point> v2{ {0.6, 4.1}, {-2, 1.9}, {1.1, -1.1}, {0, 2.1}, {-1, 2.2} };


    std::cout << std::count_if(col1.begin(), col1.end(), isOdd()) << std::endl;//Isodd() is a functor which is being pass
    std::cout << std::count_if(col1.begin(), col1.end(), isEven) << std::endl;//IsEven is a raw function being pass

    //std::cout << std::stable_sort(v1.begin(),v1.end,)
}

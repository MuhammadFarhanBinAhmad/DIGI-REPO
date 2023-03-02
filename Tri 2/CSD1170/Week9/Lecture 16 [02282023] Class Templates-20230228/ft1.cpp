#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <foward_list>

struct point
{
    double x{},y{};

    point(double dx = 0.0,double dy = 0.0) : x{dx},y{dy}{}

    double X() const {return x};
    double Y() const {return y};

}

templete<typename T>

std::ostream& operator << (std::osteram& os,std::foward_list<T> const& rhs)
{
    for (T const& x:rhs)//use const& to avoid making copy.
    {
        os << x << ' ';
    }
    return os;
}

templete<typename T>

std::ostream& operator << (std::osteram& os,std::vector<T> const& rhs)
{
    for (T const& x:rhs)//use const& to avoid making copy.
    {
        os << x << ' ';
    }
    return os;
}


std::ostream& operator <<(std::ofstream& os, point & rhs)
{
    os << "(" << rhs.X() << "," << rhs.Y() << std::endl;
}

int main(int argc,char *argv[])
{
    if (argc <2)
    {
        std::cout << "fail" << '\n';
        return 0;
    }
    std::vector<int> vi{1,2,3,4};
    std::cout << "vi" << vi << '\n';

    std::vector<std::string> vs{"a","b","c","d"};
    std::ofstream ofs{argv[1]};
    ofs << "vs: " << vs << "\n"; 

    std::vector<point> vp {point(1,2), point(2,4), point(6,8)};
    ofs << "vp: " << vp << "\n";

    std::foward_list<int> f1{1,2,3,4,5};
    std::cout << "fi :" << fi << '\n';

    std::foward_list<std::string> fs{"obama","berlin","auschwitz"};
    ofs << "city: " << fs << std::endl;
}
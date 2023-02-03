#include <string>
#include <iostream>
#include "str.hpp"

// bool foo(std::string x)
// {
//     return x.empty();
// }
namespace
{
    std::ostream& operator<<(std::ostream&,Str const&);
}
int main()
{
    // char const lisas[]{"lisa"};//legal
    // std::cout << foo(lisa) ? "empty" : "not empty\n";

    //Object create will try to initilize
    //Str s0,s1{"john"};

    Str empty,janet{"janet"} ,lisa{"lisa"},full_name;
    std::cout << "lisa"<< lisa << " | janet" << janet << '\n';

    for (size_t i{};i < janet.size();++i)
    {
        janet[i] = std::toupper(janet[i]);
    }

    std::cout << "janet" << janet <<'\n';


    //need provide begin to give length
    for (char& ch: janet)
    {
        ch = std::tolower(ch);
    }
    std::cout << "janet" << janet <<'\n';
}

namespace{
    std::ostream& operator<<(std::ostream& os,Str const& rhs)//non member function
    {
        os << '<' <<rhs.c_str()<< '>';
        return os;
    }
}
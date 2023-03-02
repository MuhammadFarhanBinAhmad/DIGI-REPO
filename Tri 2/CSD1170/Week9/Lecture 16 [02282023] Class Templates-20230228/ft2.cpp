#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <foward_list>

template<typename T>

bool larger(T const& lhs, T const& rhs)
{
    return lhs > rhs; 
}

template<typename T>

bool smaller(T const& lhs, T const& rhs)
{
    return lhs < rhs;
}

#if 1
//Be clear with templete name

template<typename Iter, typename BinPredicate>

Iter find_optium(Iter first,Iter last, BinPredicate f)
{
    Iter optimal_ptr{first++};
    while (first != last)
    {
        optimal_ptr = f(*first,*optimal_ptr) ? first : optimal_ptr;
        first++;
    }
    return optimal_ptr;
}



#else

//use poointer intead to keep track instead of copying
int find_optium(int const * first, int const *last,bool (*cmp)(int,int))//a binary premecate(return true or false)
{
    int const *optimal_ptr{*first++};

    while (first != last)
    {
        optimal_ptr = cmp(*first,*optimal_ptr) ? first : optimal_ptr;
        ++first;
    }

    return *optimal_ptr;
}

int main ()
{
    std::array <int,5> ai5{-1,0,1,2,3,4};
    std::cout << find_optium(std::begin(ai5),std::end(ai5),smaller<int>) << '\n';
    std::cout << find_optium(std::begin(ai5),std::end(ai5),larger<int>) << '\n'; 


    std::vector<std::string,5> as5{"caqt","d2sor","fasder", "sads", "urqeq"};
    std::cout << *find_optium(std::begin(as), std:: end(as),larger<std::string>);

    std::foward_list<std::string,5> fs5{"caqt","d2sor","fasder", "sads", "urqeq"};
    std::cout << *find_optium(std::begin(fs), std:: end(fs),smaller<std::string>);
}
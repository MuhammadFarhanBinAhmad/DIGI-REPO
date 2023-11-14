#include <iostream>
#include <string>
using namespace std;

//Constexpres if statement
struct Dog
{
    auto woof() const {std::cout << "woof\n";}
};

struct Cat
{
    auto Meow() const {std::cout << "meow\n";}
};
struct Duck
{
    auto quack() const {std::cout << "Quack\n";}
};


//SFINAE
template<typename Pet>
typename std::enable_if<std::is_same<Pet,Dog>::value,void>::type
noise(Pet const& pet)
{
    pet.woof();
}
template<typename Pet>
typename std::enable_if<std::is_same<Pet,Cat>::value,void>::type
noise(Pet const& pet)
{
    pet.Meow();
}

//Refer to slide 35 of consexpr presentation on week 11 HLP

#if 0
template<typename Pet>
auto noise(Pet const& pet)
{
    if constexpr(std::is_same<Pet,Dog>::value)
    {
        pet.woof();
    }
    else if constexpr(std::is_same<Pet,Cat>::value)
    {
        pet.Meow();
    }
    else if constexpr(std::is_same<Pet,Duck>::value)
    {
        pet.quack();
    }
}

/*
template <bool B , typename T = void>
struxt enable_if{};

template <typename T>
struxt enable_if<true,T>{using type = T;}

template <bool B , typename T = void>
struxt enable_if_t = enable_if(B,T)::type;
*/
#endif


int main() {
        Dog dog; Cat cat; //Duck duck;
        noise(dog);
        noise(cat);
       //noise(duck);
}
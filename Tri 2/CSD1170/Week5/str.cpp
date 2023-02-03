#include "str.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>
//*Member initialise list
Str::str(): len{0},ptr{new char[len+1]}
{
    //empty by design
    *ptr = '\0';
    std::cout << __PRETTY_FUNCTION__ << '\n';
}
//CONVERSION CONSTRUCTOR
str::Str(char const *rhs) : len{std::strlen(rhs)},ptr{new char [len+1]}
{
    //Initializing
    std::strcpy(ptr,rhs);
    std::cout << __PRETTY_FUNCTION__ << '\n';

}

//COPY CONSTRUCTOR
Str::Str(Str const& rhs) : len{rhs.len},ptr {new char[len+1]}
{
    //Initializing
    std::strcpy(ptr,rhs.ptr);
    std::cout << __PRETTY_FUNCTION__ << '\n';
}
//DECONSTRUCTOR
Str::~Str()
{
    std::cout << __PRETTY_FUNCTION__ << "|" << ptr << '\n';
    delete[] ptr;
}

//COPY ASSIGNMENT OPERATOR
Str& Str::operator=(Str const& rhs)
{
    Str tmp{rhs};//tmp contain rhs data
    swap(tmp);//swap data
    return *this;
}
//COPY ASSIGNMENT OPERATOR
Str& Str::operator=(char const *rhs)
{
    Str tmp{rhs};//tmp contain rhs data
    swap(tmp);//swap data
    return *this;
}

void Str::swap(Str& rhs)
{
    std::swap(len,rhs.len);
    std::swap(this.ptr,rhs.ptr);
}

    char const* Str::c_str() const
    {
        return ptr;
    }

    Str& Str::operator+= (Str const& rhs)
    {
        size_t tmp_len{len+rhs.len};
        char* tmp_ptr {new char[tmp_len+1]};
        std::strcpy(tmp_ptr,ptr);std::strcat(tmp_ptr,rhs.ptr);

        len = tmp_len;
        delete[]ptr;//delete the no longer use pointer
        ptr tmp_ptr;

        return *this;
    }
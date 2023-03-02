// Stackint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstddef>
class StackInt
{
public:
    using value_type = int;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
public:
    explicit StackInt(size_type);
    StackInt(StackInt const&);
    ~StackInt();
    StackInt& operator=(StackInt const&);
    void swap(StackInt&);

    void push(const_reference) {data[top_idx++] = x;}
    void pop(top_idx--) {};//Remove top element from stack
    const_reference top(return data[top_idx -1]) const;
    reference top;

    size_type max_size() const { return max_sz; }
    size_type size() const { return top_idx; }
    bool empty(return top_idx == 0);

    void print(std::ostream & = std::cout);
private:
    size_type max_sz;
    size_type top_idx;
    pointer data;
};

void StackInt::print(std::ostream& os)
{
    for (StackInt::)
}

StackInt::StackInt(StackInt::size_type s) :max_sz{ s }, top_idx{}, data{ new StackInt::value_type[max_sz] } {}

StackInt::StackInt(StackInt const& rhs) :max_sz{ rhs.max_sz }, top_idx{ rhs.top_idx }, data{ new StackInt::value_type[max_sz] }
{
    for (StackInt::size_type i{}; i < top_idx; i++)
    {
        data[i] = rhs.data[i];
    }
}

StackInt::~StackInt()
{
    delete[] data;
}

StackInt& StackInt::operator=(StackInt const& rhs)
{
    StackInt cp{ rhs };
    cp.swap(*this);
    return *this;
}

void StackInt::swap(StackInt& rhs)
{
    std::swap(max_sz,rhs.max_sz);
    std::swap(top_idx, rhs.top_idx);
    std::swap(data, rhs.data);
}

int main()
{
    StackInt si(10);
    for (int i{}; i < 5; i++)
    {
        si.push(i);
    }
    si.print(); std::cout << '\n';

    StackInt si2(1000);
    si2 = si;
    si = si2
}

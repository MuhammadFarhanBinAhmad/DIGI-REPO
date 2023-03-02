// stackt1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cstddef>
#include <iostream>
#include<vector>
#include<string>


//*NOTE:
template<typename T>
class Stack
{
public:
    using size_type = size_t;
    using value_type = T;
    using reference = value_type&;
    using const_reference = value_type const&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
public :
    //Rule of 3
    Stack(size_type);
    Stack(Stack const&);
    ~Stack();
    Stack& operator=(Stack const&);
    void swap(Stack&);
    void print(std::ostream& = std::cout);

    void push(const_reference x) { data[top_idx++] = x; }
    void pop() { --top_idx; }
    const_reference top() const { return data[top_idx - 1]; }
    reference   top() { return data[top_idx - 1]; }

    size_type max_size() const { return max_sz; }
    size_type size() const { return top_idx; }
    bool empty() const { return top_idx = 0; }
private:
    size_type max_sz, top_idx;
    pointer data;
};

template <typename T>
void Stack<T>::print(std::ostream& os)
{
    //for (typename )
}
template <typename T>
Stack<T>::Stack(typename Stack<T>::size_type s)
: max_sz{ s }, top_idx{}, data{ new T[max_sz] } 
{
    //empty by design
}

template <typename T>
Stack<T>::Stack(Stack<T> const& rhs) :
    max_sz{ rhs.max_sz }, top_idx{ rhs.top_idx }, data{ new T[max_sz] }
{
    for (typename Stack<T>::size_type i{}; i < top_idx; i++)
    {
        data[i] = rhs.data[i];
    }
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] data;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> const& rhs)
{
    Stack<T> cp{ rhs };
    cp.swap(*this);
    return *this;
}

template <typename T>
void Stack<T>::swap(Stack<T>& rhs)
{
    std::swap(max_sz, rhs.max_sz);
    std::swap(top_idx, rhs.top_idx);
    std::swap(data, rhs.data);

}

int main()
{
    Stack<int> si(10);
    for (Stack<int>::size_type i{}; i < 5; i++)
    {
        si.push(i);
    }
    Stack<int> si2(1000);
    si2 = si;
    std::cout << si2.max_size() << " | " << si2.size() << '\n';
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

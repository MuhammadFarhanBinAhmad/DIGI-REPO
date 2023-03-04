
#ifndef LISTINT_H
#define LISTINT_H

#include <cstddef>
#include <iostream>
#include <initializer_list>
// Declare this as a friend function in class ListInt:
namespace hlp2
{
    class ListInt {
    public:
    // type aliases
    using size_type = size_t;
    using value_type = int;
    public:
    ListInt();
    ListInt(const ListInt&);
    ListInt(std::initializer_list<value_type>);
    ~ListInt();

    ListInt& operator=(ListInt);
    ListInt& operator=(std::initializer_list<value_type>);

    ListInt &operator+=(const ListInt &);
    ListInt& operator+=(ListInt &&);

    value_type& operator[](size_type);
    const value_type& operator[](size_type) const;

    
    ListInt operator+(const ListInt&) const;
    ListInt operator+(const std::initializer_list<ListInt::value_type>& rhs) const;
    friend ListInt operator+(std::initializer_list<ListInt::value_type> other_list,const ListInt& rhs);

    void push_front(value_type);
    void push_back(value_type);

    value_type pop_front();

    void clear();
    void swap(ListInt&);

    size_type size();
    bool empty() const;
    // interface
    static size_type object_count();

    friend std::ostream& operator<<(std::ostream& os, const ListInt& rhs);

    private:
     struct Node {
        int data; // the actual data in the node
        Node *next; // pointer to the next Node

        Node(value_type val): data(val), next(nullptr){}
    };
    Node *head {nullptr}; // pointer to the head of the list
    Node *tail {nullptr}; // pointer to the last node
    static size_type object_counter; // number of nodes on the list
    Node* new_node(value_type data) const;    
    };


std::ostream& operator<<(std::ostream& os, const ListInt& rhs);

#endif 

}
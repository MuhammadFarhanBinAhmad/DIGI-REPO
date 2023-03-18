// File header documentation is required!!!

// Follow other guidelines and practices from previous assessments
#ifndef SLLIST_HPP_
#define SLLIST_HPP_
// add this non-member, non-friend function template declaration:
#include <iostream>
#include <initializer_list>
#include <iomanip>

namespace hlp2
{
    template <typename T>
    class sllist
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using reference = value_type &;
        using const_reference = const value_type &;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = pointer;
        using const_reverse_iterator = const_pointer;

    public:
        struct Node
        {
            Node *next{nullptr}; // pointer to next Node
            value_type data;     // actual data of type int in node
            Node(T const &);     // conversion ctor to initialize Node object
            ~Node();             // dtor
            // count of Nodes created [by currently instantiated lists]
            static size_type node_counter; // declaration
        };

        Node *new_node( const_reference) const;
        Node *head{nullptr};
        Node *tail{nullptr};

        static size_type object_counter;
        size_type counter{0};

    public:
        sllist();
        sllist(sllist const &rhs);
        sllist(std::initializer_list<T> const &);
        sllist(const_pointer begin, const_pointer end);
        ~sllist();

        int data(Node const *p);        // accessor to node's data
        void data(Node *p, int newval); // mutator to node's data
        Node *next(Node *p);            // pointer to successor node
        Node *next(Node const *p) const;
        //  interface declarations for singly-linked list...
        bool empty() const;
        size_t size() const;
        void push_front(value_type const &ptr_sll);
        void push_back(value_type const &ptr_sll);
        void remove_first(int value);
        void clear();
        void swap(sllist<T> &rhs);
        reference front();
        const_reference front() const;
        void pop_front();

        sllist<value_type> &operator+=(sllist const &);
        sllist<value_type> &operator+=(std::initializer_list<value_type> const &);
        sllist &operator=(sllist const &rhs);
        sllist &operator=(std::initializer_list<value_type> const &_list);

        static size_t node_count();
        static size_t object_count();

        reference operator[](size_type);
        const_reference operator[](size_type) const;

        template <typename U>
        friend std::ostream &operator<<(std::ostream &os, const sllist<U> &rhs);
    };

    template <typename T>
    void swap(sllist<T> &lhs, sllist<T> &rhs);
    template <typename T>
    sllist<T> operator+(const std::initializer_list<T> &lhs, const sllist<T> &rhs);
    template <typename T>
    sllist<T> operator+(const sllist<T> &lhs, const std::initializer_list<T> &rhs);
    template <typename T>
    sllist<T> operator+(const sllist<T> &lhs, const sllist<T> &rhs);

    template <typename T>
    typename sllist<T>::size_type sllist<T>::object_counter{0};
    template <typename T>
    typename sllist<T>::size_type sllist<T>::Node::node_counter{0};
}

#include "sllist.tpp"
#endif
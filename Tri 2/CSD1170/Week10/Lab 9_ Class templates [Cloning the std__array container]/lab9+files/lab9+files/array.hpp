/******************************************************************************/
/*!
\file   array.tpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 8: Cloning std::array<T,N> using Class Templates
\date   10/03/2022
\brief
   1. 18 member functions:
    begin()
    begin() const
    end()
    end() const
    cbegin() const
    cend() const
    front()
    front() const
    back()
    back() const
    operator[]()
    operator[]() const
    empty() const
    data()
    data() const
    size() const
    fill()
    swap()
   2. non-member functions:
    swap()
    operator==()
    operator!=()
    operator>()
    operator<()
*/
//-------------------------------------------------------------------------
#ifndef ARRAY_HPP_
#define ARRAY_HPP_
//-------------------------------------------------------------------------

#include <cstddef> // for size_t
#include <initializer_list>

// Otherwise, your submission will not compile!!!

namespace hlp2
{

    template <typename T, size_t N>
    class Array
    {
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = pointer;
        using const_iterator = const_pointer;

    public:
        Array() = default;
        Array(std::initializer_list<value_type>const& rhs);
        ~Array() = default;

        pointer begin();
        const_pointer begin() const;
        const_pointer cbegin() const;

        pointer end();
        const_pointer end() const;
        const_pointer cend() const;

        reference front();
        const_reference front() const;

        reference back();
        const_reference back() const;

        reference operator[](size_t);
        const_reference operator[](size_t) const;

        bool empty() const;
        pointer data();
        const_pointer data() const;

        size_type size() const;

        void fill(value_type const &);
        void swap(Array<T, N> &);

    public:
        value_type m_Array[N];
    };
    template <typename T, size_t N>
    void swap(Array<T, N> &, Array<T, N> &);
    template <typename T, size_t N>
    bool operator==(Array<T, N> const &, Array<T, N> const &);
    template <typename T, size_t N>
    bool operator!=(Array<T, N> const &, Array<T, N> const &);
    template <typename T, size_t N>
    bool operator>(Array<T, N> const &, Array<T, N> const &);
    template <typename T, size_t N>
    bool operator<(Array<T, N> const &, Array<T, N> const &);

// Define class template Array<T,N> and document each member function

// Declare and document non-member functions

// EVERY member and non-member function must be defined
// in separate file array.tpp
} // end namespace hlp2
#include "array.tpp"

#endif // end ARRAY_HPP_

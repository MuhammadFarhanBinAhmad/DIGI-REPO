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
#include "array.hpp"

namespace hlp2
{
    //Copy assignment constructor
    template <typename T, size_t N>
    Array<T, N>::Array(std::initializer_list<T> const &rhs) : m_Array{}
    {
        for (size_t index = 0; index < rhs.size(); index++)
        {
            this->m_Array[index] = rhs.begin()[index];
        }
    }
    //begin() function return a pointer of the start of the array
    template <typename T, size_t N>
    typename Array<T, N>::pointer Array<T, N>::begin() { return this->m_Array; }

    template <typename T, size_t N>
    typename Array<T, N>::const_pointer Array<T, N>::begin() const { return this->m_Array; }

    template <typename T, size_t N>
    typename Array<T, N>::const_pointer Array<T, N>::cbegin() const { return this->m_Array; }

    //end() function return a pointer that poits to the last element in the array
    template <typename T, size_t N>
    typename Array<T, N>::pointer Array<T, N>::end() { return this->m_Array + N; }

    template <typename T, size_t N>
    typename Array<T, N>::const_pointer Array<T, N>::end() const { return this->m_Array + N; }

    template <typename T, size_t N>
    typename Array<T, N>::const_pointer Array<T, N>::cend() const { return this->m_Array + N; }

    //front() return 1st element in the array
    template <typename T, size_t N>
    typename Array<T, N>::reference Array<T, N>::front() { return this->m_Array[0]; }

    template <typename T, size_t N>
    typename Array<T, N>::const_reference Array<T, N>::front() const { return this->m_Array[0]; }

    //back() return last element in the array
    template <typename T, size_t N>
    typename Array<T, N>::reference Array<T, N>::back() { return this->m_Array[N - 1]; }

    template <typename T, size_t N>
    typename Array<T, N>::const_reference Array<T, N>::back() const { return this->m_Array[N - 1]; }

    //return value of a desire index
    template <typename T, size_t N>
    typename Array<T, N>::reference Array<T, N>::operator[](size_t index)
    {
        return this->m_Array[index];
    }
    template <typename T, size_t N>
    typename Array<T, N>::const_reference Array<T, N>::operator[](size_t index) const
    {
        return this->m_Array[index];
    }

    //empty return a bool that state if the array is empty or not
    template <typename T, size_t N>
    bool Array<T, N>::empty() const
    {
        return (this->m_Array == nullptr);
    }

    //data() return a pointer to the first element in the array object. 
    template <typename T, size_t N>
    typename Array<T, N>::pointer Array<T, N>::data() { return this->m_Array; }

    template <typename T, size_t N>
    typename Array<T, N>::const_pointer Array<T, N>::data() const { return this->m_Array; }

    //return size of the array
    template <typename T, size_t N>
    typename Array<T, N>::size_type Array<T, N>::size() const
    {
        return N;
    }

    //fill array with desired value
    template <typename T, size_t N>
    void Array<T, N>::fill(value_type const &rhs)
    {
        std::fill(this->begin(), this->end(), rhs);
    }

    //Swap array
    template <typename T, size_t N>
    void Array<T, N>::swap(Array<T, N> &rhs)
    {
        std::swap(this->m_Array, rhs.m_Array);
    }

    // NON MEMBER FUNCTION
    template <typename T, size_t N>
    void swap(Array<T, N> &rhs, Array<T, N> &lhs)
    {
        rhs.swap(lhs);
    }
    // NON MEMBER FUNCTION

    //Check if both array are equal return true if is equal
    template <typename T, size_t N>
    bool operator==(Array<T, N> const &rhs, Array<T, N> const &lhs)
    {
        return (std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    //Check if both array are not equal return true if is not equal
    template <typename T, size_t N>
    bool operator!=(Array<T, N> const &lhs, Array<T, N> const &rhs)
    {
        return !(lhs == rhs);
    }
    //Check if the lhs array is bigger than rhs array
    template <typename T, size_t N>
    bool operator>(const Array<T, N> &lhs, Array<T, N> const &rhs)
    {
        return !std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && (lhs != rhs);
    }
    //Check if the lhs array is smaller than rhs array
    template <typename T, size_t N>
    bool operator<(const Array<T, N> &lhs, Array<T, N> const &rhs)
    {
        return !(lhs > rhs) && (lhs != rhs);
    }

}

/******************************************************************************/
/*!
\file   vct.hpp
\author *Insert name here :)
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Assignment 6: vector Template Abstract Data Type
\date   07/03/2022
\brief
    4 constructor
     1. default constructors
     2. non-default conversion constructor(size_t)
     3. non-default conversion constructor(initialuzer_list<int>)
     4. copy constructor
    1 destructor
    2 = operator
     1. vector paramater
     2. initializer_list<int> parameter
    2 [] operator
    reserve - Allocate more memory
    resize - Resize container so that it can contain the assign amount of element
    push_back - Add a new element at the end of the array
    empty - Check if array is empty
    size - Get size of array
    capacity - Get capacity of array
    allocation - Get how many time the array size got allocated
    Iterators -
    3 begin - Returns first element
    3 end - Return last element
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef VCT_HPP
#define VCT_HPP
////////////////////////////////////////////////////////////////////////////////
#include <initializer_list>
#include <iostream>
namespace hlp2
{
    template <typename T>
    class vector
    {
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = value_type *;
        using const_pointer = const value_type *;
        using reference = value_type &;
        using const_reference = const value_type &;

    public:
        // Initialize vector with default value
        vector();
        // Initialize vector with a certain size and capacity
        vector(size_type n);
        // Initialize vector with a certain size and capacity
        vector(value_type rhs);
        vector(vector const &rhs);
        vector(std::initializer_list<T> rhs);
        ~vector();
        vector &operator=(vector const &vec);
        vector &operator=(value_type rhs);
        reference operator[](size_type index);
        const_reference operator[](size_type index) const;
        void push_back(T value);
        void reserve(size_type newsize);
        void resize(size_type newsize);
        void swap(vector &rhs);
        void pop_back();
        bool empty() const;
        // return size value of vector
        size_type size() const;
        // return space value of vector
        size_type capacity() const;
        // return the value of how many time the vector alloc space
        size_type allocations() const;
        // return first value
        pointer begin();
        // return last value
        pointer end();
        const_pointer begin() const;
        const_pointer end() const;
        const_pointer cbegin() const;
        const_pointer cend() const;

    private:
        size_type sz;     // the number of elements in the array
        size_type space;  // the allocated size (in terms of elements) of the array
        size_type allocs; // number of times space has been updated
        pointer data;     // the dynamically allocated array
    };
    //Mafan but if a class uses template, need set template for all fuction and return type must also be template
    //Thats because the class itself does not know what type it is yet as they will only know it during compile time as the class will be instiate there
    //Also need template return type cause, again, the member function does kow it's own return type.:)
    template <typename T>
    vector<T>::vector() : sz{0}, space{0}, allocs{0}, data{nullptr}
    {
    }
    // Initialize vector with a certain size and capacity
    template <typename T>
    vector<T>::vector(size_type n)
    {
        // copy size and space for old array
        this->sz = n;
        this->space = n;
        this->allocs = 1;
        data = new value_type[n];
    }
    // Initialize vector with a certain size and capacity
    template <typename T>
    vector<T>::vector(value_type rhs)
    {
        // copy size and space for old array
        sz = rhs.size();
        space = rhs.size();
        // alloc set to one since size of array being change
        allocs = 1;
        data = new value_type[rhs.size()]; // Pointer point to the newly created array
        // Copy element from old array to this new array
        const value_type *temp = rhs.begin();
        for (size_type i = 0; i < rhs.size(); i++)
        {
            data[i] = *(temp++);
        }
    }
    template <typename T>
    vector<T>::vector(std::initializer_list<T> rhs)
    {
        //copy size and space for old array
        sz = rhs.size();
        space = rhs.size();
        //alloc set to one since size of array being change
        allocs =1;
        data = new value_type[rhs.size()];//Pointer point to the newly created array
        //Copy element from old array to this new array
        const value_type *temp = rhs.begin();
        for (size_type i =0; i < rhs.size();i++)
        {
            data[i] = *(temp++);
        }
    }
    template <typename T>
    vector<T>::vector(vector const &rhs)
    {
        // copy size and space for old array
        sz = rhs.sz;
        space = sz;
        // alloc set to one since size of array being change
        allocs = 1;

        data = new value_type[rhs.sz]; // Pointer point to the newly created array
        // Copy element from old array to this new array
        for (size_type i = 0; i < sz; i++)
        {
            data[i] = rhs.data[i];
        }
    }
    template <typename T>
    vector<T>::~vector()
    {
        delete[] data;
    }
    template <typename T>
    typename vector<T>::vector &vector<T>::operator=(vector const &vec)
    {
        this->allocs++;
        this->sz = vec.sz;
        this->space = vec.sz;
        pointer temp = new value_type[vec.sz]; // need create new temp to copy
        // copy data from old array into the newly created array
        for (size_type i = 0; i < this->sz; i++)
        {
            temp[i] = vec.data[i];
        }
        delete[] this->data; // delete old array
        this->data = temp;   // point pointer to the new array

        return *this;
    }
    template <typename T>
    typename vector<T>::vector &vector<T>::operator=(value_type rhs)
    {
        const value_type *temp = rhs.begin();
        sz = rhs.size();
        space = sz;
        allocs++;
        data = new value_type[rhs.size()];
        // copy data from old array into the newly created array
        for (size_type i = 0; i < rhs.size(); i++)
        {
            data[i] = *(temp++);
        }
        return *this;
    }
    template <typename T>
    typename vector<T>::reference vector<T>::operator[](size_type index)
    {
        return *(data + index);
    }
    template <typename T>
    typename vector<T>::const_reference vector<T>::operator[](size_type index) const
    {
        return *(data + index);
    }
    template <typename T>
    void vector<T>::push_back(T value)
    {
        // if space zero, allocate space for 1 new element
        if (space == 0)
        {
            reserve(1);
            data[sz++] = value;
        }
        // if size and space equal to the same value, double space size and allocate new value
        else if (sz == space)
        {
            reserve(space * 2);
            data[sz++] = value;
        }
        // allocate new value into array
        else
        {
            data[sz++] = value;
        }
    }
    template <typename T>
    void vector<T>::reserve(size_type newsize)
    {
        // check if newsize value is larger or smaller
        // if smaller, then dont do anything
        if (newsize <= this->space)
        {
            return;
        }
        // If larger then neeed allocate more space
        pointer temp = new value_type[newsize]; // need create new temp to copy
        // copy data from old array into new array
        for (size_type i = 0; i < this->sz; i++)
        {
            temp[i] = this->data[i];
        }
        delete[] this->data; // delete old array
        data = temp;         // point at the new array
        space = newsize;
        allocs++;
    }
    template <typename T>
    void vector<T>::resize(size_type newsize)
    {
        // if same valie, dont do anything
        if (sz == newsize)
        {
            return;
        }
        // if newsize is lesser than current size,just change value of size to newsize
        if (newsize < sz)
        {
            sz = newsize;
        }
        // if new size is bigger than space, need allocate more space
        if (newsize > space)
        {
            reserve(newsize);
            sz = newsize;
        }
    }
    //swap 2 vector
    template <typename T>
    void vector<T>::swap(vector &rhs)
    {
        std::swap(sz,rhs.sz);
        std::swap(space,rhs.space);
        std::swap(allocs,rhs.allocs);
        std::swap(data,rhs.data);
    }
    //Remove last element in array
    template <typename T>
    void vector<T>::pop_back()
    {
        this->sz--;
    }
    template <typename T>
    bool vector<T>::empty() const
    {
        return sz==0;
    }
    // return size value of vector
    template <typename T>
    typename vector<T>::size_type vector<T>::size() const
    {
        return this->sz;
    }
    // return space value of vector
    template <typename T>
    typename vector<T>::size_type vector<T>::capacity() const
    {
        return this->space;
    }
    // return the value of how many time the vector alloc space
    template <typename T>
    typename vector<T>::size_type vector<T>::allocations() const
    {
        return this->allocs;
    }
    // return first value
    template <typename T>
    typename vector<T>::pointer vector<T>::begin()
    {
        return this->data;
    }
    // return last value
    template <typename T>
    typename vector<T>::pointer vector<T>::end()
    {
        return this->data + this->sz;
    }
    template <typename T>
    typename vector<T>::const_pointer vector<T>::begin() const
    {
        return this->data;
    }
    template <typename T>
    typename vector<T>::const_pointer vector<T>::end() const
    {
        return this->data + this->sz;
    }
    template <typename T>
    typename vector<T>::const_pointer vector<T>::cbegin() const
    {
        return this->data;
    }
    template <typename T>
    typename vector<T>::const_pointer vector<T>::cend() const
    {
        return this->data + this->sz;
    }

} // namespace hlp2

#endif // VCT_HPP

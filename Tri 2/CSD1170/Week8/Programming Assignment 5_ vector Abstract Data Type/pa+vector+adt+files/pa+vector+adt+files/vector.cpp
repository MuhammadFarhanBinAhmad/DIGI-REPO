// make sure to have a file-level Doxygen documentation block!!!
// read the specs to know which standard library headers cannot be included!!!
/******************************************************************************/
/*!
\file   vector.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Assignment 5: vector Abstract Data Type
\date   22/02/2022
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
#include <iostream>
#include "vector.hpp"
namespace hlp2
{
    //Initialize vector with default value
    vector::vector():sz{0},space{0},allocs{0},data{nullptr}
    {

    }
    //Initialize vector with a certain size and capacity
    vector::vector(size_type n)
    {
        //copy size and space for old array
        this->sz = n;
        this->space = n;
        this->allocs = 1;
        data = new value_type[n];
    }
    //Initialize vector with a certain size and capacity
    vector::vector(std::initializer_list<int> rhs)
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
    vector::vector(vector const& rhs)
    {
        //copy size and space for old array
        sz = rhs.sz;
        space = sz;
        //alloc set to one since size of array being change
        allocs = 1;

        data = new value_type[rhs.sz];//Pointer point to the newly created array
        //Copy element from old array to this new array
        for (size_type i =0; i < sz ;i++)
        {
            data[i] = rhs.data[i];
        }
    }
    vector::~vector()
    {
        delete[] data;
    }
    vector& vector::operator=(vector const& vec)
    {
        this->allocs++;
        this->sz = vec.sz;
        this->space = vec.sz;
        pointer temp =  new value_type[vec.sz];//need create new temp to copy
        //copy data from old array into the newly created array
        for (size_type i =0; i < this->sz;i++)
        {
            temp[i] = vec.data[i];
        }
        delete [] this->data;//delete old array
        this->data = temp;//point pointer to the new array

        return *this;
    }
    vector& vector::operator=(std::initializer_list<int> rhs)
    {
        const value_type *temp = rhs.begin();
        sz = rhs.size();
        space = sz;
        allocs++;
        data = new value_type[rhs.size()];
        //copy data from old array into the newly created array
        for (size_type i =0; i < rhs.size();i++)
        {
            data[i] = *(temp++);
        }
        return *this;
    }
    vector::reference vector::operator[](size_type index)
    {
        return *(data+index);
    }
    vector::const_reference vector::operator[](size_type index) const
    {
        return *(data+index);
    }
    void vector::push_back(value_type value)
    {
        //if space zero, allocate space for 1 new element
        if (space == 0)
        {
            reserve(1);
            data[sz++] = value;
        }
        //if size and space equal to the same value, double space size and allocate new value
        else if (sz == space)
        {
            reserve(space*2);
            data[sz++] = value;
        }
        //allocate new value into array
        else
        {
            data[sz++] = value;
        }
        
    }
    void vector::reserve(size_type newsize)
    {
        //check if newsize value is larger or smaller
        //if smaller, then dont do anything
        if (newsize <= this->space)
        {
            return;
        }
        //If larger then neeed allocate more space
        pointer temp =  new value_type[newsize];//need create new temp to copy
        //copy data from old array into new array
        for (size_type i =0; i < this->sz;i++)
        {
            temp[i] = this->data[i];
        }
        delete [] this->data;//delete old array
        data = temp;//point at the new array
        space = newsize;
        allocs++;
    }
    void vector::resize(size_type newsize)
    {
        //if same valie, dont do anything
        if (sz == newsize)
        {
            return;
        }
        //if newsize is lesser than current size,just change value of size to newsize
        if (newsize < sz)
        {
            sz = newsize;
        }
        //if new size is bigger than space, need allocate more space
        if (newsize > space)
        {
            reserve(newsize);
        }
    }
    bool vector::empty() const
    {
        //just check if data is pointing to anything
        if (!this->data)
        {
            return false;
        }
        return true;
    }
    //return size value of vector
    vector::size_type vector::size() const
    {
        return this->sz;
    }
    //return space value of vector
    vector::size_type vector::capacity() const
    {
        return this->space;
    }
    //return the value of how many time the vector alloc space
    vector::size_type  vector::allocations() const
    {
        return this->allocs;
    }
    //return first value
    vector::pointer vector::begin()
    {
        return this->data;
    }
    //return last value
    vector::pointer vector::end()
    {
        return this->data + this->sz;
    }
    vector::const_pointer vector::begin() const
    {
        return this->data;
    }
    vector::const_pointer vector::end() const
    {
        return this->data + this->sz;
    }
    vector::const_pointer vector::cbegin() const
    {
        return this->data;
    }
    vector::const_pointer vector::cend() const
    {
        return this->data + this->sz;
    }
} // namespace hlp2

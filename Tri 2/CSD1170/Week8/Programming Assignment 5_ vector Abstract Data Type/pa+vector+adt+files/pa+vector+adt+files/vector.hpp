// make sure to have a file-level Doxygen documentation block AND
// function-level documentation block for each function that your
// client will be using!!!
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
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_HPP
#define VECTOR_HPP
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>          // need this for size_t
#include <initializer_list> // need this for std::initializer_list<int>
// read the specs to know which standard library headers cannot be included!!!
 
namespace hlp2 {
	
  class vector {

  public:
    // @todo: using declarations required!!!
    // types to declare: size_type, value_type,
    // reference, const_reference, pointer, const_pointer
    using size_type = size_t;
    using value_type = int;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

  public:
    // @todo: declare default constructor

    // i'am providing this declaration
      // @todo: declare non-default ctor for std::initializer_list<int>
    // @todo: declare copy ctor
    // @todo: declare destructor
    // @todo: declare copy assignment operator for assignment with vector object
    // @todo: declare copy assignment operator for std::initializer_list<int>
    // @todo: declare overloaded subscript operator and overload subscript
    // operator for const objects
    vector(); // default ctor
  explicit vector(size_type n); // non-default, conversion ctor
  vector(std::initializer_list<int> rhs); // non-default, conversion ctor
  vector(vector const& rhs); // copy ctor
  ~vector();
  vector& operator=(vector const&);
  vector& operator=(std::initializer_list<int> rhs);
  value_type operator-();
  reference operator[](size_type index);
  const_reference operator[](size_type index) const;

    // i'am declaring push_back(), reserve(), and resize()
  void push_back(value_type value);
  void reserve(size_type newsize);
  void resize(size_type newsize);
    

  bool empty() const; // is container empty?
  size_type size() const; // what is sz?
  size_type capacity() const; // what is space?
    // @todo: declare empty()
    // @todo: declare size()
    // @todo: declare capacity()

    // i'am declaring allocations()
  size_type allocations() const;
    
    // @todo: declare iterators [described in spec]
  pointer begin(); // pointer to first element
  pointer end(); // pointer to one past last element
  const_pointer begin() const;
  const_pointer end() const;
  const_pointer cbegin() const;
  const_pointer cend() const;
  private:
    size_type sz;     // the number of elements in the array
    size_type space;  // the allocated size (in terms of elements) of the array
    size_type allocs; // number of times space has been updated
    pointer   data;   // the dynamically allocated array
  };

} // namespace hlp2
#endif // VECTOR_HPP

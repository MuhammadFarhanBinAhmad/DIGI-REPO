// make sure to add file-level documentation here!!!
/******************************************************************************/
/*!
\file   vector.cpp
\author Muhammad Farhan Bin Ahmad
\par    email: b.muhammadfarhan@digipen.edu
\par    DigiPen login: b.muhammadfarhan
\par    Course: CS1170
\par    Section A
\par    Lab 7: Half-Open Ranges with Function Templates
\date   24/02/2022
\brief
  count - Count total amount of a certain value
  copy - Copy element from one array to another
  display - Print out value
  equal - Check if 2 array are equal to one another
  find - Find and return position of an element position
  fill - Find array with desired value
  min_element - Find the smallest value between 2 value 
  max_element - Find the largest value between 2 value 
  remove - Remove element of a certain type/value from an array
  replace - Replace certain value of element in array with a new value
  swap_ranges - Swap ranges between 2 array
  swap - Swap position of 2 array
  sum - Return total sum
*/
//-------------------------------------------------------------------------
#ifndef FT_H
#define FT_H
//-------------------------------------------------------------------------
#include <iostream>
// Do not add any other header files. Otherwise, your submission
// will not compile!!!

namespace hlp2
{
  // DECLARE (not define!!!) and DOCUMENT in ALPHABETIC ORDER the function
  // templates you'll be defining. There are *13* function templates to be
  // declared and defined.


  template <typename T1, typename T2>
  int count(T1 *start, T1 *end, T2 value);

  template <typename T>
  T* copy(const T *start, const T *end, T *cont);

  template <typename T>
  void display(T *lhs,  T* rhs);

  template <typename T1,typename T2>
  bool equal(T1 *start, T1 *end, T2 *comp);

  template <typename T1, typename T2>
  T1 find( T1 start,  T1 end, T2 find);

  template <typename T1,typename T2>
  void fill(T1 *start, T1 *end, T2 value);

  template <typename T>
  T *min_element(T *start, T *end);

  template <typename T>
  T *max_element(T *start, T *end);

  template <typename T>
  T *remove(T *start, T *end, T value);

  template <typename T1, typename T2>
  void replace(T1 *start, T1 *end, const T2 old_Value, const T2 new_Value);

  template <typename T>
  void swap_ranges(T *start, T *end, T *swap_cont);

  template <typename T>
  void swap(T &lhs, T &rhs);

  template <typename T>
  T sum(T *start, T *end);
  // I'm providing the declaration and documentation for swap here:
  /***************************************************************************/
  /*!
  \brief
   Swaps two objects. There is no return value but the two objects are
   swapped in place.

  \param lhs
    Reference to the first object to swap.

  \param rhs
   Reference to the second object to swap.
  */
  /**************************************************************************/
  template <typename T1, typename T2>
  int count(T1 *start, T1 *end, T2 value)
  {
    int c = 0;//counter
    while (start != end)
    {
      //if value is same, plus counter
      if (*start == value)
      {
        c++;
      }
      start++;//move to next element
    }
    return c;
  }
  template <typename T>
  T* copy(const T *start, const T *end, T *cont)
  {
    while (start != end)
    {
      *cont++ = *start++;//assign 2nd array current element with 1st array current element
    }
    return cont;
  }

  template <typename T>
  void display(T *start,  T* end)
  {
    //I LOVE FORMATTING
    while (start != end)
    {
      std::cout << *start;
      
      if (start != end -1)
      {
        std::cout<< ", ";
      }
      start++;
    }
    std::cout << '\n';
  }

  template <typename T1,typename T2>
  bool equal(T1 *start, T1 *end, T2 *comp)
  {
    //Check till last element
    while (start != end)
    {
      //return false if current element doesnt equal to the other element 
      if (*start != *comp)
      {
        return false;
      }
      comp++;
      start++;
    }
    return true;
  }
  template <typename T1, typename T2>
  T1 find( T1 start,  T1 end, T2 find)
  {
    while (start != end)
    {
      //return position of the of the array
      if (*start == find)
      {
        return start;
      }
      start++;
    }
    return start;
  }

  template <typename T1,typename T2>
  void fill(T1 *start, T1 *end, T2 value)
  {
    //fill element in array with value
    while (start != end)
    {
      *start = value;
      start++;
    }
  }

  template <typename T>
  T *min_element(T *start, T *end)
  {
    //return pointer of the smaller element
    T * temp = start;
    while (start != end)
    {
      if (*start < *temp)
      {
        temp = start;
      }
      start++;
    }
    return temp;
  }

  template <typename T>
  T *max_element(T *start, T *end)
  {
    //return pointer of the larger element
    T * temp = start;
    while (start != end)
    {
      if (*temp < *start)
      {
        temp = start;
      }
      start++;
    }
    return temp;
  }
  template <typename T>
  T *remove(T *start, T *end, T value)
  {
    //loop through array
    while (start < end)
    {
      //if value wish to remove is meet
      if (*start == value)
      {
        //push all element to the front
        T* temp = start;
        while (temp < end -1)
        {
          *temp = *(temp+1);
          temp++;
        }
        end--;
      }
      else{
      start++;
      }
    }
    return end;
  }

  template <typename T1, typename T2>
  void replace(T1 *start, T1 *end, const T2 old_Value, const T2 new_Value)
  {
    //Replace selected element with new element
    while (start != end)
    {
      if (*start == old_Value)
      {
        *start = new_Value;
      }
      start++;
    }
  }

  template <typename T>
  void swap_ranges(T *start, T *end, T *swap_cont)
  {
    //Replace a range of element with another array
    while (start != end)
    {
      swap(*start, *swap_cont);
      start++;
      swap_cont++;
    }
  }

  template <typename T>
  void swap(T &lhs, T &rhs)
  {
    //swap value
    T temp = lhs;
    lhs = rhs;
    rhs = temp;
  }

  template <typename T>
  T sum(T *start, T *end)
  {
    //find total sum
    T total {};//assign {} because unsure what type they sending
    while (start != end)
    {
      total += *start;
      start++;
    }
    return total;
  }
}

#endif
//-------------------------------------------------------------------------

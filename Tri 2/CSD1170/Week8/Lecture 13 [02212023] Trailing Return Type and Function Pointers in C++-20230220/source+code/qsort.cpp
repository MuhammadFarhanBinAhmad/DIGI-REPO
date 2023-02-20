// HLP2 05/26/2020
// qsort.cpp:
// Illustrates the use of function pointers as callback functions using
// C standard library function qsort

/*
A pointer to a function is a perfectly reasonable type, which
means a function can have a parameter of this type as well. The function can
then use its function pointer parameter to call the function to which the
argument points when the function was called. You can specify just a function
name as an argument for a parameter that is a "pointer to function" type.
A function passed to another function as an argument is referred to as a
callback function, the function that accepts another function as a parameter
is a higher-order function.

The declaration of function qsort looks like this:

void qsort(void *ptr, std::size_t count, std::size_t size, int (*cmp_func)(const void*, const void*));
where ptr points to the 1st element of array to be sorted,
count is the number of items in the array,
size is the size in one bytes of each item, and
cmp_func is a pointer to a comparison function that takes two void pointers and returns an int.

Behavior of comparison callback:
if left item is bigger than right item,   return positive value
if right item is bigger than left item,   return negative value
if left item is equivalent to right item, return 0 
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstddef> // for size_t

// comparison function for sorting int values in ascending order ...
int int_lt(void const *pleft, void const *pright) {
  return *static_cast<int const*>(pleft) - *static_cast<int const*>(pright);
}

// comparison function for sorting int values in descending order ...
int int_gt(void const *pleft, void const *pright) {
  return *static_cast<int const*>(pright) - *static_cast<int const*>(pleft);
}

// comparison function for sorting double values in ascending order ...
int dbl_lt(void const *pleft, void const *pright) {
  return *(double const*)pleft - *(double const*)pright;
}

// comparison function for sorting double values in descending order ...
int dbl_gt(void const *pleft, void const *pright) {
  return *(double const*)pright - *(double const*)pleft;
}

// overloaded functions for printing ranges of array elements
void print(int const *first, int const *last, 
          std::string const& prefix, std::string const &postfix = "\n") {
  std::cout << prefix;
  while (first != last) {
    std::cout << *first << ' ';
    ++first;
  }
  std::cout << postfix;
}

void print(double const *first, double const *last, 
          std::string const& prefix, std::string const &postfix = "\n") {
  std::cout << prefix;
  while (first != last) {
    std::cout << *first << ' ';
    ++first;
  }
  std::cout << postfix;
}

int main() {
  // our array size is 5 elements ...
  const size_t SIZE {5};
  int ia[SIZE] {11, -4, 4, -10, 6};
  
  // call qsort to sort int array elements in ascending order 
  qsort(ia, SIZE, sizeof(int), int_lt);
  print(ia, ia+SIZE, "ia: ");

  // call qsort to sort int array elements in descending order 
  qsort(ia, SIZE, sizeof(int), int_gt);
  print(ia, ia+SIZE, "ia: ");

  double da[SIZE] = {11.1, -4.1, 4.1, -10.1, 6.1};
  // call qsort to sort double array elements in ascending order 
  qsort(da, SIZE, sizeof(double), dbl_lt);
  print(da, da+SIZE, "da: ");

  // call qsort to sort double array elements in descending order 
  qsort(da, SIZE, sizeof(double), dbl_gt);
  print(da, da+SIZE, "da: ");
}

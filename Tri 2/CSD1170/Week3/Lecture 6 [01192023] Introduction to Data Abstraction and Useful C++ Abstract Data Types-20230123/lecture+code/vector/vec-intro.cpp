/*
HLP2: vec-intro.cpp
01/25/2022

The following program defines a vector for integer values, inserts 
six elements, and prints the vector elements to standard output.

Before looking at the code, read the following brief introduction to vectors.
The vector type, defined in <vector>, is a library type that is a container
that holds a sequence of values of a specified type and lets us get at each
individual value efficiently. vectors grow dynamically. A vector  enables 
random access, which means that you can access each element directly with 
the corresponding index. Appending and removing elements at the end of the 
array is very fast. However, inserting an element in the middle or at the 
beginning of the array takes time because all the following elements have 
to be moved to make room for it while maintaining the order.

Some important operations:
vector<T>::size_type - A type guaranteed to be able to hold the number of
                     elements in the largest possible vector.
vector<T> v    - Creates an empty vector that can hold elements of type T.
v.push_back(e) - Grows the vector by one element initialized to e.
v[i]           - Returns the value stored in position i.
v.size()       - Returns the number of elements in v.
*/
#include <vector>
#include <iostream>

int main() {
  std::vector<int> vc;	// vector container for integer elements

  // append elements with values 1 to 6
  for (int i = 1; i <= 6; ++i) {
    vc.push_back(i);
  }

  // print all elements followed by a space
  for (std::vector<int>::size_type i = 0; i < vc.size(); ++i) {
    std::cout << vc[i] << ' ';
  }
  std::cout << '\n';
}
/*
HLP2: vec-algo.cpp
01/25/2022
The following program provides a brief introduction to the concept
of algorithms in the STL. We use some commonly used algorithms to apply a 
variety of algorithms on a vector<int> container.

Before looking at the code, read the following brief introduction to algorithms.
The STL provides several standard algorithms for processing elements of
collections. These algorithms offer general fundamental services such as
searching, sorting, copying, reordering, modifying, and numeric processing.
Algorithms are not member functions of the container classes but instead are
global template functions that operate with iterators. This has an important
advantage: Instead of each algorithm being implemented for each container type,
they are implemented only once for any container type. The algorithm might even
operate on elements of different container types. You can also use algorithms for
user-defined container types. All in all, this concept reduces the amount of code
and increases the power and flexibility of the library.
Note that this is not an OOP paradigm; it is a generic functional programming
paradigm. Instead of data and operations being unified, as in OOP, they are
separated into distinct parts that can interact via a certain interface. However,
this concept also has its price: First, the usage is not intuitive. Second, some
combinations of data structures and algorithms might not work. Even worse, a
combination of a container type and an algorithm might be possible but not useful
(for example, it may lead to bad performance). Therefore, it is important to learn
the concepts and pitfalls of the STL to benefit from it without abusing it.

The following program illustrates some algorithms and their usage:
*/
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
  // create vector with elements from 1 to 6 in arbitrary order
  std::vector<int> vc{2, 5, 4, 1, 6, 3 };
  
  // find and print minimum and maximum elements
  std::vector<int>::const_iterator minpos = std::min_element(vc.cbegin(), vc.cend());
  std::vector<int>::const_iterator maxpos = std::max_element(vc.cbegin(), vc.cend());
  std::cout << "max:<" << *minpos << "> and min:<" << *maxpos << ">" << "\n";

/*
The above two algorithms are called with two parameters that define the range of
the processed elements. To process all elements of a container, you simply use
cbegin() and cend() or begin() and end(), respectively. Both algorithms return an
iterator for the position of the element found.
*/

  // sort all elements
  std::sort(vc.begin(), vc.end());

/*
As the name indicates, sort() sorts the elements of the range defined by the two
arguments with the default sorting criterion of operator <. Thus, the elements
in the container above would be sorted in ascending order. It is also possible
to pass You could pass an optional sorting criterion. Note that we can't use
cbegin() and cend() here because sort() modifies the values of the elements, which
is not possible for const_iterators.
*/

  // find the first element with value 3
  // note that we are not using cbegin() and cend() because we'll modify the
  // element pos3 refers to
  std::vector<int>::iterator pos3 = std::find(vc.begin(), vc.end(),	// range
                                              3);										// value
/*
The find() algorithm searches for a value inside the given range. In the above
call, find() searches for the first element that is equal to the value 3 in the
whole container. If find() is successful, it returns the iterator position of the
element found. If the algorithm fails, it returns the end of the range passed as
second argument, which is the past-the-end iterator of vc.
*/											

  // reverse the order of found element with value 3 and all following elements
  std::reverse(pos3, vc.end());
  
  // print all elements
  for (std::vector<int>::value_type const &elem : vc) {
    std::cout << elem << ' ';
  }
  std::cout << "\n";
}

/*
HLP2: vec-iterator.cpp
01/25/2022
The following program provides a brief introduction to the concept
of iterators. We use iterators to traverse a vector<char> container
and perform both read and write operations on the elements of the container.

Before looking at the code, read the following brief introduction to iterators.
An iterator is a value that
- Identifies a container and an element in the container
- Lets us examine the value stored in that element
- Provides operations for moving between elements in the container
- Restricts the available operations in ways that correspond to what the
container can handle efficiently.

The following fundamental operations define the behavior of an iterator:
1. operator* returns the element of the current position. If the elements
have members, you can use operator -> to access those members directly
from the iterator.
2. operator++ lets the iterator step forward to the next element. Most
iterators also allow stepping backward by using operator--.
3. operators == and != return whether two iterators represent the same
position.
4. operator = assigns an iterator (the position of the element to which
it refers).

These operations provide exactly the interface of ordinary pointers in C/C++
when these pointers are used to iterate over the elements of an ordinary
array. The difference is that iterators may be smart pointers - pointers
that iterate over more complicated data structures of containers. The internal
behavior of iterators depends on the data structure over which they iterate.
Hence, each container type supplies its own kind of iterator. As a result,
iterators share the same interface but have differnet types. This leads directly
to the concept of generic programming: Operations use the same interface but
different types, so you can use templates to formulate generic operations that
work with arbitrary types that satisfy the interface.

All container classes provide the same basic member functions that enable them
to use iterators to navigate over their elements. The most important of these
functions are as follows:
1. begin() returns an iterator to represent the beginning of the elements in
the container. The beginning is the position of the first element, if any.
2. end() returns an iterator that represents the end of the elements in the
container. The end is the position behind the last element. Such an iterator
is also called a past-the-end iterator.

Thus, begin() and end() define a half-open range that includes the first element
but excludes the last. A half-open range has two advantages:
1. It allows a simple end criterion for loops that iterator over elements: they
simply continue as long as end() is not reached.
2. It avoids special handling for empty ranges. For empty ranges, begin() is
equal to end().

Every standard container, such as vecotr, defines two associated iterator types:

  container-type::const_iterator
  container-type::iterator
  
where container-type is the container type, such as vector<int> or vector<string>,
that includes the type of the container elements. When we want to use an iterator
to change the values stored in the container, we use the iterator type. If we
need only read access, then we use the const_iterator type.
*/
#include <vector>
#include <iostream>

int main() {
  std::vector<char> vc; // vector container for character elements
  
  // add elements from 'a' to 'z'
  for (char c = 'a'; c <= 'z'; ++c) {
    vc.push_back(c);
  }
  
  // print all elements:
  // - iterate over all elements
  std::cout << "original set: ";
  for (std::vector<char>::const_iterator pos = vc.begin(); pos != vc.end(); ++pos) {
    std::cout << *pos;
  }
  std::cout << "\n";
/*
++pos versus pos++
------------------
Note the use of the preincrement operator (prefix ++) to move the iterator to the
next element. The reason is that it will have better performance than the post-
increment operator. The latter internally involves a temporary object because it
must return the old position of the iterator (more about this latter in the semester).
For this reason, it generally is better to prefer ++pos over pos++. Thus, you should
avoid the following version:

  for (pos = vc.begin(); pos != vc.end(); pos++) {	// OK, but slightly lower efficiency
  }
*/
  
  // convert all lowercase characters to uppercase
  std::cout << "altered set:  ";
  for (std::vector<char>::iterator pos = vc.begin(); pos != vc.end(); ++pos) {
    *pos = std::islower(*pos) ?  std::toupper(*pos) : *pos;
  }
/*
In C++11, we can declare a variable or an object without specifying its specific
type by using auto. For example:

  auto i = 42;	// i has type int
  double foo();		// declaration of f
  auto d = foo();	// d has type double
  
The type of a variable declared with auto is deduced from its initializer. Thus,
an initialization is required:

  auto i;	// ERROR: can't deduce the type of i
  
Additional qualifiers are allowed. For example:

  static auto sa = 0.19; // sa is an object of type double with static extent
  
Using auto is especially useful where the type is quite long and/or complicated
expression. Thus, we can use the keyword auto to specify the exact type of the
iterator provided that you initialize the iterator during its declaration so that
its type can be derived from the initial value. Thus, by initializing the iterator
directly with begin(), you can use auto to declare its type.
As can be seen, one advantage of using auto is that the code is more condensed.
The other advantage is that the loop is robust when modifications are required
such as when the type of the container is changed. However, the drawback is that the
iterator loses its constness, which might raise the risk of unintended assignments.
With
  auto pos = vc.begin()
pos becomes a nonconstant iterator because begin() returns an object of type
cont::iterator. To ensure that constant iterators are still used, cbegin() and
cend() are provided as container functions since C++11. They return an object of
type cont::const_iterator.
To summarize the improvements, since C++11, a loop that allows iterating over all
the elements of a container without using a range-based for loop might look as
follows:
*/
  for (auto pos = vc.cbegin(); pos != vc.cend(); ++pos) {
    std::cout << *pos;
  }
  std::cout << "\n";
}

// Note that we'll not be using keyword auto during the HLP2 module!!!

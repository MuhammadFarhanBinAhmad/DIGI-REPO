#ifndef STACKVECSTR_HPP
#define STACKVECSTR_HPP

/*
You can specialize a class template for certain template arguments. Similar
to the overloading of function templates, specializing class templates allows
you to optimize implementations for certain types or to fix a misbehavir of
certain types for an instantiation of the class template. However, if you
specialize a class template, you must also specialize all member functions.

To specialze a class template, you've to declare the class with a leading
template<> and a specification of the types for which the class template is
specialized. The types are used as a template argument and must be specialized
directly following the name of the class:

template <>
class Stack<std::string> {
  ...
};

For these specializations, any definition of a member function must be defined
as an "ordinary" member function, with each occurrence of T being replaced by
the specialized type:

void Stack<std::string>::push(std::string const& elem) { elems.push_back(elem); }

Here is a complete example of a specializaton of Stack<> for type std::string.
As part of the "specialization", we use a std::deque<std::string> instead of a
std::vector<std::string> to manage the elements inside the stack. Although there
is no particular benefit here, it does demonstrate that the implementation of a
specialization might look very different from the implementation of the
primary template.
*/

#include "stackvec.hpp"
#include <deque>
#include <string>
#include <iostream>

template <>
class Stack<std::string> {
public:
  using size_type       = std::deque<std::string>::size_type;
  using value_type      = std::deque<std::string>::value_type;
  using reference       = std::deque<std::string>::reference;
  using const_reference = std::deque<std::string>::const_reference;

public:
  Stack() = default;
  Stack(Stack const&) = default;
  Stack& operator=(Stack const&) = default;
  Stack(std::deque<std::string> const&); // define single-argument constructor
  ~Stack() = default;

  void push(const_reference elem); // push element
  void pop();                      // pop element
  const_reference top() const;     // return read-only reference to top element
  reference       top();           // return reference to top element
  bool empty() const;              // return whether the Stack is empty
  size_type size() const;          // return number of elements in Stack

  friend std::ostream& operator<<(std::ostream&, Stack<std::string> const&);

private:
  std::deque<std::string> elems; // one reason for Stack<std::string> to be "special"
                                 // is that it requires std::deque<> as container 
                                 // while Stack<T> uses std::vector
};

// to define a member function of a class template, you've to specify that it
// is a template, and you've to use the full type qualification of the class
// template:
Stack<std::string>::Stack(std::deque<std::string> const& rhs) : elems{rhs} {
  // empty by design
}

void Stack<std::string>::push(const_reference elem) {
  elems.push_back(elem); // append copy of passed elem using vector<>::push_back()
}

void Stack<std::string>::pop() {
  elems.pop_back();
}

Stack<std::string>::const_reference Stack<std::string>::top() const {
  return elems.back(); // return last element
}

Stack<std::string>::reference Stack<std::string>::top() {
  return elems.back(); // return last element
}

bool Stack<std::string>::empty() const { 
  return elems.empty();
}

Stack<std::string>::size_type Stack<std::string>::size() const {
  return elems.size();
}

// define function that overloads operator<< for Stack<std::string>:
// note: this is not a function template since Stack<std::string> is
// a concrete class!!!
std::ostream& operator<<(std::ostream& os, Stack<std::string> const& rhs) {
  // to print contents of private member elems, we must make this
  // function a friend of class Stack<std::string>
  for (std::string const& x : rhs.elems) { os << x << ' '; }
  return os;
}

#endif // end of #ifndef STACKVECSTR_HPP

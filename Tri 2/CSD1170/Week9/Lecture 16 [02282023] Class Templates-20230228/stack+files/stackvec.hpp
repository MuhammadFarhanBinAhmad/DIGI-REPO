/*
Previously, we implemented class template<> by explicitly implementing
low level memory management, copy constructor, and assignment operator.
We can follow DRY (Don't Repeat Yourself) principles by using a class
template of the C++ standard library: vector<>. This allows us to concentrate
on the interface of this class template:
*/
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#include <vector>
#include <iostream>

template <typename T>
class Stack {
public:
  using size_type       = typename std::vector<T>::size_type;
  using value_type      = typename std::vector<T>::value_type;
  using reference       = typename std::vector<T>::reference;
  using const_reference = typename std::vector<T>::const_reference;

public:
  Stack() = default;
  Stack(Stack const&) = default;
  Stack& operator=(Stack const&) = default;
  Stack(std::vector<T> const&); // define single-argument constructor
  ~Stack() = default;

  void push(const_reference elem); // push element
  void pop();                      // pop element
  const_reference top() const;     // return read-only reference to top element
  reference       top();           // return reference to top element
  bool empty() const;              // return whether the Stack is empty
  size_type size() const;          // return number of elements in Stack

  // declare function template operator<< as friend function. However, using T
  // again will hide the outer T and will therefore not work. Skipping the
  // template parameter declaration would not work since we would then be
  // declaring a template function as a non-template function
  // Instead, we implicitly declare a new function template that will use a
  // different template parameter such as U:
  template <typename U>
  friend std::ostream& operator<<(std::ostream&, Stack<U> const&);

private:
  std::vector<T> elems; // elements
};

// to define a member function of a class template, you've to specify that it
// is a template, and you've to use the full type qualification of the class
// template:
template <typename T>
Stack<T>::Stack(std::vector<T> const& rhs) : elems{rhs} {
  // empty by design
}

template <typename T>
void Stack<T>::push(const_reference elem) {
  elems.push_back(elem); // append copy of passed elem using vector<>::push_back()
}

template <typename T>
void Stack<T>::pop() {
  elems.pop_back();
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() const {
  return elems.back(); // return last element
}

template <typename T>
typename Stack<T>::reference Stack<T>::top() {
  return elems.back(); // return last element
}

template <typename T>
bool Stack<T>::empty() const { 
  return elems.empty();
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
  return elems.size();
}

#if 0
// define function template that overloads operator<< for std::pair<>.
// note: this assumes that both types T1 and T2 have overloads for
// operator<<!!!
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& rhs) {
  os << "{" << rhs.first << ", " << rhs.second << "} ";
  return os;
}
#endif

// define function template that overloads operator<< for Stack<>:
template <typename T>
std::ostream& operator<<(std::ostream& os, Stack<T> const& rhs) {
  // to print contents of vector<> member elems, we must make this
  // function a friend of class Stack<T>
  for (T const& x : rhs.elems) { os << x << ' '; }
  return os;
}

#endif // end of #ifndef STACKVEC_HPP

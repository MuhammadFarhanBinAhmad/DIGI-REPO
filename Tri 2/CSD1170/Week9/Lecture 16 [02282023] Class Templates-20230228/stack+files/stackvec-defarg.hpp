/*
As for function templates, you can define default values for class template
parameters. For example, in class Stack<>, you can define the container that
is used to manage the elements as a second template parameter, using
std::vector<> as the default value:
*/
#ifndef STACKVEC_DEFARG_HPP
#define STACKVEC_DEFARG_HPP

#include <vector>
#include <deque>
#include <iostream>

template <typename T, typename Cont = std::vector<T>>
class Stack {
public:
  using size_type       = typename Cont::size_type;
  using value_type      = typename Cont::value_type;
  using reference       = typename Cont::reference;
  using const_reference = typename Cont::const_reference;

public:
  Stack() = default;
  Stack(Stack const& rhs) = default;
  Stack& operator=(Stack const&) = default;
  Stack(Cont const&); // define single-argument constructor
  ~Stack() = default;

  void push(const_reference elem); // push element
  void pop();                      // pop element
  const_reference top() const;     // return read-only reference to top element
  reference       top();           // return reference to top element
  bool empty() const;              // return whether the Stack is empty
  size_type size() const;          // return number of elements in Stack

  // declare function template operator<< as friend function. However, using
  // T and Cont again will hide the outer T and Cont and will therefore not
  // work. Skipping the template parameter declaration would not work since
  // we would then be declaring a template function as a non-template function
  // Instead, we implicitly declare a new function template that will use
  // different template parameters such as U and V:
  template <typename U, typename V>
  friend std::ostream& operator<<(std::ostream&, Stack<U, V> const&);

private:
  Cont elems; // elements
};

// to define a member function of a class template, you've to specify that it
// is a template, and you've to use the full type qualification of the class
// template:
template <typename T, typename Cont>
Stack<T, Cont>::Stack(Cont const& rhs) : elems{rhs} {
  // empty by design
}

template <typename T, typename Cont>
void Stack<T, Cont>::push(const_reference elem) {
  elems.push_back(elem); // append copy of passed elem using vector<>::push_back()
}

template <typename T, typename Cont>
void Stack<T, Cont>::pop() {
  elems.pop_back();
}

template <typename T, typename Cont>
typename Stack<T, Cont>::const_reference Stack<T, Cont>::top() const {
  return elems.back(); // return last element
}

template <typename T, typename Cont>
typename Stack<T, Cont>::reference Stack<T, Cont>::top() {
  return elems.back(); // return last element
}

template <typename T, typename Cont>
bool Stack<T, Cont>::empty() const { 
  return elems.empty();
}

template <typename T, typename Cont>
typename Stack<T, Cont>::size_type Stack<T, Cont>::size() const {
  return elems.size();
}

// define function template that overloads operator<< for std::pair<>.
// note: this assumes that both types T1 and T2 have overloads for
// operator<<!!!
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& rhs) {
  os << "{" << rhs.first << ", " << rhs.second << "} ";
  return os;
}

// define function template that overloads operator<< for Stack<T, Cont>:
template <typename T, typename Cont>
std::ostream& operator<<(std::ostream& os, Stack<T, Cont> const& rhs) {
  // to print contents of vector<> member elems, we must make this
  // function a friend of class Stack<T>
  for (T const& x : rhs.elems) { os << x << ' '; }
  return os;
}

#endif // end of #ifndef STACKVEC_DEFARG_HPP

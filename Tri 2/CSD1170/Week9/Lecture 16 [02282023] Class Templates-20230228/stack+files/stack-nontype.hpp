/*
In contrast to the previous implementations of a stack, you can also implement
it stack by using a fixed-size array for the elements. An advantage of this
method is that the memory management overhead, whether performed by you or
by a standard container, is avoided. However, determining the best size for
such a stack can be challenging. The smaller the size you specify, the more
likely it is tht the stack will get full. The larger the size you specify,
the more likely it is that memory will be reserved unnecessarily. A good
solution is to let the user of the stack specify the size of the array as
the maximum size needed for stack elements.
*/
#ifndef STACK_NONTYPE_HPP
#define STACK_NONTYPE_HPP

#include <array>
#include <iostream>

// the user of the stack will specify the size of the array as the
// maximum size needed for stack elements - this is done by defining
// the size as a template parameter
template <typename T, size_t MaxSize>
class Stack {
public:
  using size_type = typename std::array<T, MaxSize>::size_type;
  using value_type = typename std::array<T, MaxSize>::value_type;
  using reference = typename std::array<T, MaxSize>::reference;
  using const_reference = typename std::array<T, MaxSize>::const_reference;
private:
  std::array<T, MaxSize> elems;
  size_type num_elems;
public:
  Stack() : num_elems{0} {}

  void push(const_reference elem);
  void pop() { --num_elems; }
  reference top() { return elems[num_elems-1]; }
  const_reference top() const { return elems[num_elems-1]; }

  bool empty() const { return num_elems==0; }
  size_type size() const { return num_elems; }

  // non-member function template that is given friendship
  template <typename U, size_t V>
  friend std::ostream& operator<<(std::ostream&, Stack<U,V> const&);
};

template <typename T, size_t MaxSize>
void Stack<T, MaxSize>::push(const_reference elem) {
  elems[num_elems++] = elem;
}

// provide overload for operator<< for std::pair<T1, T2>
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1,T2> const& p) {
  os << "{" << p.first << ", " << p.second << "} ";
  return os;
}

template <typename T, size_t MaxSize>
std::ostream& operator<<(std::ostream& os, Stack<T,MaxSize> const& rhs) {
  for (typename Stack<T,MaxSize>::size_type i{0};
       i < rhs.num_elems; ++i) {
    os << rhs.elems[i] << ' ';
  }
  return os;
}

#endif

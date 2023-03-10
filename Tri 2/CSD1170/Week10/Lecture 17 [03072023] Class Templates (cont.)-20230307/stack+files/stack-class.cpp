// HLP2: stack-class.cpp
// Definitions of member functions of classes StackChar and StackStr

#include "stack-class.hpp"
#ifdef DEBUG
#include <iostream>
#endif

StackChar::StackChar(size_type sz) 
: max_sz{sz}, top_idx{0}, v{new value_type [max_sz]} {
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

StackChar::StackChar(StackChar const& rhs)
: max_sz{rhs.max_sz}, top_idx{rhs.top_idx}, v{new value_type [max_sz]} {
  for (size_type i{0}; i < top_idx; ++i) {
    v[i] = rhs.v[i];
  }
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

StackChar::~StackChar() {
  delete [] v;
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

void StackChar::push(const_reference val) {
  v[top_idx++] = val;
}

void StackChar::pop() {
  --top_idx;
}

StackChar::reference StackChar::top() {
  return v[top_idx-1];
}

StackChar::const_reference StackChar::top() const {
  return v[top_idx-1];
}

bool StackChar::empty() const {
  return top_idx==0;
}

StackChar::size_type StackChar::size() const {
  return top_idx;
}

StackChar::size_type StackChar::max_size() const {
  return max_sz;
}
////////////////////////////////////////////////////////////////

StackStr::StackStr(size_type sz) 
: max_sz{sz}, top_idx{0}, v{new value_type [max_sz]} {
  // empty by design
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

StackStr::StackStr(StackStr const& rhs)
: max_sz{rhs.max_sz}, top_idx{rhs.top_idx}, v{new value_type [max_sz]} {
  for (size_type i{0}; i < top_idx; ++i) {
    v[i] = rhs.v[i];
  }
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

StackStr::~StackStr() {
  delete [] v;
#ifdef DEBUG
    std::cout << __PRETTY_FUNCTION__ << "\n";
#endif
}

void StackStr::push(const_reference val) {
  v[top_idx++] = val;
}

void StackStr::pop() {
  --top_idx;
}

StackStr::reference StackStr::top() {
  return v[top_idx-1];
}

StackStr::const_reference StackStr::top() const {
  return v[top_idx-1];
}

bool StackStr::empty() const {
  return top_idx==0;
}

StackStr::size_type StackStr::size() const {
  return top_idx;
}

StackStr::size_type StackStr::max_size() const {
  return max_sz;
}

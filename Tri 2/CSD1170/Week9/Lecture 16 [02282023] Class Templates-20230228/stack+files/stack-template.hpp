/*
Finally, we're at a stage where we've used C++ classes to create types
StackChar and StackStr that follow principles of abstraction and 
encapsulation (that is, the interface/implementation methodology). Using ctors
and dtors, it is harder for clients to introduce memory leaks. However, one
major problem is that the type designer has created StackChar type that can
only manage a stack of chars and duplicated that effort to create a StackStr
type. What if clients would like to organize a stack of integers, a stack of
Students, a stack of StopWatchs, a stack of linked lists, or a stack of arrays,
and so on? Class designers would then have to implement the same behavior again
and again for each of the different types (chars, ints, linked lists, ...). In
other words, designers have to constantly reinvent the wheel.

C++ solves this problem using templates - they're functions or classes that are
written for one or more types not yet specified. When clients use a template, they
pass the type as arguments, explicitly or implicitly. Templates are THE MOST
IMPORTANT FEATURE of Modern C++ - they're used extensively. The C++ standard
library is almost completely implemented using templates.

Template code is a little different from ordinary code. When the compiler sees
client code, as in:

Stack<int> sc(10); // create a Stack of 10 ints

it must first instantiate the specific type (in this case a Stack<int>) from a 
generic template provided by the template designer (in this case a Stack<T> for 
some unknown type T). Next, the compiler must instantiate an object (in this
case sc) of the specific type (in this case Stack<int>). For the compiler to
complete the first step, it must be aware of the specific type for which the
class must be instantiated (in this case Stack<int>) so that it can replace the
generic type T with the concrete type int.

We've learnt to organize our nontemplate code largely as follows:
1) Classes and other types and declarations are placed in header files (.h).
2) For global variables and (noninline) functions, only a declaration is placed
in the header file, and the definition goes into a source file (.cpp). This works
well with nontemplated code - it makes the needed type definitions available
throughout a client's program and avoids duplicate definition errors on variables
and functions from the linker.

This model doesn't work with templated code. Assume, as usual, stack-template.h
contains the template class definition while noninline member functions are
implemented in stack-template.cpp. Now, consider a client's source file
stack-template-driver.cpp with a definition, as in:

Stack<int> sc(10);

When compiling stack-template-driver.cpp, the compiler is unable to instantiate 
type Stack<int> from the template type defined in stack-template.h because the 
defintions of noninline functions of the generic class Stack are defined in
stack-template.cpp which is inaccessible to the compiler (because it is compiling
source file stack-template-driver.cpp and a compiler can only compile a single
source file at a time).

The simplest and most common way to solve the conundrum is to copy the noninline
member functions of generic type Stack from stack-template.cpp and paste them in
stack-template.hpp after the definition of the generic type.
*/
#include <cstddef> // for size_t

template <typename T>
class Stack {
public:
  using value_type      = T;
  using size_type       = size_t;
  using reference       = value_type&;
  using const_reference = value_type const&;

public: // the interface
  explicit Stack(size_type sz); // single-arg conversion ctor
  Stack(Stack const& rhs);      // copy ctor
  ~Stack();                     // dtor 

  // Adds element above top of the Stack
  // Notice that we passing a reference to a read-only object
  // This is because we don't the size of the object and therefore
  // we must pass by reference for our implementation to be
  // efficient. We pass a reference to read-only object because we
  // "promise" clients that the ctor will not alter the state of
  // the object using the reference ...
  void push(const_reference val);
  
  // removes element at top of the Stack -
  // effectively reducing its size by one
  void pop();

  // returns a reference to the top element in Stack 
  reference top();
  const_reference top() const;
  
  // returns whether the Stack is empty - that is, has zero elements
  bool empty() const;

  // returns the number of elements in Stack
  size_type size() const;

  // returns the maximum number of elements that can be stored in Stack
  size_type max_size() const;

private: // the implementation
  size_type max_sz;  // maximum possible number of elements in Stack
  size_type top_idx; // index (in memory pointed to by v) to top of Stack
  value_type *v;      // pointer to 1st element in block of memory on free store
};

// definitions of member functions of template type Stack<T>

// single-argument conversion ctor definition
template <typename T> // this tells the compiler that we are defining a template function
Stack<T>::Stack(size_type sz) // Stack<T> is the scope created by the template class
: max_sz{sz}, top_idx{0}, v{new value_type [max_sz]} { 
#ifdef DEBUG
  std::cout << "Calling ctor Stack::Stack(size_t)" << "\n";
#endif
}

// copy ctor definition
template <typename T>
Stack<T>::Stack(Stack<T> const& rhs)
: max_sz{rhs.max_sz}, top_idx{rhs.max_sz}, v{new value_type [max_sz]} {
  for (size_type i{0}; i < top_idx; ++i) {
    v[i] = rhs.v[i];
  }
#ifdef DEBUG
  std::cout << "Calling dtor Stack::~Stack(Stack const&)" << "\n";
#endif
}

// dtor definition
template <typename T>
Stack<T>::~Stack() {
  delete [] v;
#ifdef DEBUG
  std::cout << "Calling ctor Stack::~Stack()" << "\n";
#endif
}

// all remaining functions ...
template <typename T>
void Stack<T>::push(const_reference value) {
  v[top_idx++] = value;
}

template <typename T>
void Stack<T>::pop() {
  --top_idx;
}

template <typename T>
typename Stack<T>::reference Stack<T>::top() {
  return v[top_idx-1];
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() const {
  return v[top_idx-1];
}

template <typename T>
bool Stack<T>::empty() const {
  return top_idx == 0;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::size() const {
  return top_idx;
}

template <typename T>
typename Stack<T>::size_type Stack<T>::max_size() const {
  return max_sz;
}

/*
To pass the preprocessor macro name DEBUG to g++ and clang++, use the -D opton:
g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror -DDEBUG stack-class.cpp stack-template-driver.cpp
*/

#include <iostream>           // for std::cout
#include <string>             // for std::string
#include <cassert>            // for assert macro
#include "stack-class.hpp"    // for StackChar and StackStr
#include "stack-template.hpp" // for Stack<T>

// declarations of functions performing unit tests for stacks defined in stack-class.cpp
void test_stack_char();
void test_stack_str();
void test_stack_template();

// exercise the implementation of the interface/implementation in stack-template.hpp
int main() {
  std::cout << "--------------- Testing Stack<T> ---------------\n";
  test_stack_template();
  std::cout << "--------------- Testing StackChar ---------------\n";
  test_stack_char();
  std::cout << "--------------- Testing StackStr ---------------\n";
  test_stack_str();
}

// definitions of test drivers ...
void test_stack_template() {
  // unlike the previous version (StackChar and StackStr),
  // clients can define stacks of any type currently being used in their programs
  // (and those that haven't been yet invented)

  // s1 is an object of type Stack<char> - that is, it is a container 
  // that is an abstraction of the Stack data type for chars ...
  Stack<char> s1(10);
  s1.push('o'); s1.push('l'); s1.push('l'); s1.push('e'); s1.push('h');
  ++++s1.top(); // change 'h' to 'j'
  while (!s1.empty()) {
    std::cout << s1.top() << " ";
    s1.pop();
  }
  std::cout << "\n";

  // s2 is object of type Stack<std::string> - that is, it is a container 
  // that is an abstraction of the Stack data type for strings ...
  Stack<std::string> s2(15);
  s2.push("day"); s2.push("good"); s2.push("a");
  s2.push("is"); s2.push("today");
  while (!s2.empty()) {
    std::cout << s2.top() << " ";
    s2.pop();
  }
  std::cout << "\n";

  // ps3 is a pointer to an object of type Stack<int> that is
  // defined on the heap - the new operator will ensure that the
  // ctor is automatically invoked right after the memory is allocated
  // to initialize the allocated memory ...
  Stack<int> *ps3 { new Stack<int>(20) };
  for (int i = 9; i >= 0; --i) {
    ps3->push(i);
  }
  while (!ps3->empty()) {
    std::cout << ps3->top() << " ";
    ps3->pop();
  }
  std::cout << "\n";
  
  delete ps3; // dtor invoked by system ...
}

// definitions of test driver for StackChar ...
void test_stack_char() {
  // s1 is an object of type StackChar - that is, s1 is an instance
  // (in memory) of a type defined in C++ using either a struct or class
  { // create a new block scope for s1 to check if ctor/dtor are called ...
  StackChar s1(10); // ctor is "automatically" invoked by the compiler ...
  std::cout << "sizeof(StackChar): " << sizeof(StackChar) << " | sizeof(s1): " << sizeof(s1) << "\n";
  // clients use the struture/class member operator to access members 
  std::cout << "Max elements in s1: " << s1.max_size() << "\n";
  s1.push('o'); s1.push('l'); s1.push('l'); s1.push('e'); s1.push('h');
  std::cout << "Element count in s1: " << s1.size() << "\n";
  while (!s1.empty()) {
    std::cout << s1.top();
    s1.pop();
  }
  std::cout << "\n";
  
  if (s1.empty() == true) {
    std::cout << "Stack s1 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s1 is NOT empty" << "\n";
  }
  } // end of scope for s1 - its dtor will now be invoked ...

  // s2 is another object of type StackChar
  { // create another block scope for object s2 to check if ctor and dtor
    // are being automatically invoked ...
  StackChar s2(100); // ctor must now be invoked for s2
  s2.push('y'); s2.push('a'); s2.push('c');
  // since s2 is not a read-only object, it calls the non-const version 
  // of the top() function rather than the const version.
  ++s2.top(); // top() returns a reference - changes 'c' to 'd'
  while (!s2.empty()) {
    std::cout << s2.top();
    s2.pop();
  }
  std::cout << "\n";
  if (s2.empty() == true) {
    std::cout << "Stack s2 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s2 is NOT empty" << "\n";
  }
  } // end of scope for s2 - its dtor will now be invoked ...

  // ps3 is of type pointer to StackChar - therefore, we must instantiate
  // an object of type StackChar on the heap and make ps3 point to this
  // instantiated object
  // the ctor for the StackChar object being defined on the heap will now
  // be automatically invoked by the new operator ...
  StackChar *ps3 = new StackChar(1000); // pass argument 1000 to ctor
  // since ps3 is of type StackChar*, we use the arrow operator to access
  // public members ...
  std::cout << "Max elements in object pointed to by ps3: " << ps3->max_size() << "\n";
  ps3->push('y'); ps3->push('a'); ps3->push('d');

  // test copy ctor!!!
  StackChar s4(*ps3);
  assert(s4.size() == ps3->size());

  std::cout << "Element count in object pointed to by ps3: " << ps3->size() << "\n";
  while (!ps3->empty()) {
    std::cout << ps3->top();
    ps3->pop();
  }
  std::cout << "\n";
  if (ps3->empty() == true) {
    std::cout << "Stack ps3 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack ps3 is NOT empty" << "\n";
  }

  // to prevent memory leaks, we must return previously instantiated heap
  // object back to the system ...
  delete ps3; // dtor for StackChar object on heap will be automatically invoked
  
  s4.push('y'); s4.push('a'); s4.push('d');
  assert(s4.size() == 6);
  std::cout << "Element count in object pointed to by s4: " << s4.size() << "\n";
  while (!s4.empty()) {
    std::cout << s4.top();
    s4.pop();
  }
  std::cout << "\n";
  if (s4.empty() == true) {
    std::cout << "Stack s4 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s4 is NOT empty" << "\n";
  }
}

// definitions of test driver for StackStr ...
void test_stack_str() {
  // s1 is an object of type StackStr - that is, s1 is an instance
  // (in memory) of a type defined in C++ using either a struct or class
  { // create a new block scope for s1 to check if ctor/dtor are called ...
  StackStr s1(10); // ctor is "automatically" invoked by the compiler ...
  std::cout << "sizeof(StackStr): " << sizeof(StackStr) 
            << " | sizeof(s1): " << sizeof(s1) << "\n";
  // clients use the struture/class member operator to access members 
  std::cout << "Max elements in s1: " << s1.max_size() << "\n";
  s1.push("o"); s1.push("l"); s1.push("l"); s1.push("e"); s1.push("h");
  std::cout << "Element count in s1: " << s1.size() << "\n";
  while (!s1.empty()) {
    std::cout << s1.top();
    s1.pop();
  }
  std::cout << "\n";
  
  if (s1.empty() == true) {
    std::cout << "Stack s1 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s1 is NOT empty" << "\n";
  }
  } // end of scope for s1 - its dtor will now be invoked ...

  // s2 is another object of type StackStr
  { // create another block scope for object s2 to check if ctor and dtor
    // are being automatically invoked ...
  StackStr s2(100); // ctor must now be invoked for s2
  s2.push("y"); s2.push("a"); s2.push("c");
  // since s2 is not a read-only object, it calls the non-const version 
  // of the top() function rather than the const version.
  s2.top() = "d"; // top() returns a reference - changes "c" to "d"
  while (!s2.empty()) {
    std::cout << s2.top();
    s2.pop();
  }
  std::cout << "\n";
  if (s2.empty() == true) {
    std::cout << "Stack s2 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s2 is NOT empty" << "\n";
  }
  } // end of scope for s2 - its dtor will now be invoked ...
  
  // ps3 is of type pointer to StackStr - therefore, we must instantiate
  // an object of type StackStr on the heap and make ps3 point to this
  // instantiated object
  // the ctor for the StackStr object being defined on the heap will now
  // be automatically invoked by the new operator ...
  StackStr *ps3 = new StackStr(1000); // pass argument 1000 to ctor
  // since ps3 has type StackStr*, arrow operator is required to access public members
  std::cout << "Max elements in object pointed to by ps3: "
            << ps3->max_size() << "\n";
  ps3->push("Guten Tag"); ps3->push("Nin Hao"); ps3->push("Zdravstvuyte");
  std::cout << "Element count in object pointed to by ps3: "
            << ps3->size() << "\n";

  // test copy ctor!!!
  StackStr s4(*ps3);
  assert(s4.size() == ps3->size());


  while (!ps3->empty()) {
    std::cout << ps3->top();
    ps3->pop();
  }
  std::cout << "\n";
  if (ps3->empty() == true) {
    std::cout << "Stack ps3 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack ps3 is NOT empty" << "\n";
  }

  // to prevent memory leaks, we must return previously instantiated heap
  // object back to the system ...
  delete ps3; // dtor for StackChar object on heap will be automatically invoked ...

  s4.push("Hello"); s4.push("Bonjour"); s4.push("Konnichiwa");
  assert(s4.size() == 6);
  std::cout << "Element count in object pointed to by s4: " << s4.size() << "\n";
  while (!s4.empty()) {
    std::cout << s4.top() << " ";
    s4.pop();
  }
  std::cout << "\n";
  if (s4.empty() == true) {
    std::cout << "Stack s4 is empty" << "\n";
  } else {
    std::cout << "Impossible: Stack s4 is NOT empty" << "\n";
  }
}

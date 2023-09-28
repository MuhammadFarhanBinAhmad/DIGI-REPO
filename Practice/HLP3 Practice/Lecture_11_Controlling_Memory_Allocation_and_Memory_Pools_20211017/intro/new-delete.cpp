/*
CSD2125 10/11
new-delete.cpp
This source file shows how to redefine the various operator new
and operator delete overloads ...

Compile/link: g++ -std=c++17 new-delete.cpp str.cpp -o new-delete.out
*/
#include <iostream>
#include <new>
#include <cstdlib>
#include "str.h"
#include <string>

// redefinition of global operator new function ...
void* operator new(std::size_t count) {
  std::cout << __PRETTY_FUNCTION__ << " | count: " << count << "\n";

  // handle zero-byte requests as one-byte requests
  count = (count == 0) ? 1 : count;

  while (1) {
    // attempt to allocate byte on free store
    void *ptr = std::malloc(count);
    // if allocation was successful, return pointer to memory
    if (ptr) {
      return ptr;
    }

    // allocation is unsuccessful
    std::new_handler nh = std::get_new_handler();
    if (nh) {
      (*nh)();
    } else {
      throw std::bad_alloc();
    }
  }
}

// redefinition of global operator delete function ...
void operator delete(void *raw_memory) noexcept {
  std::cout << __PRETTY_FUNCTION__ << "\n";

  // deallocate the memory
  // free does nothing if null pointer is being deleted
  free(raw_memory);
}

// redefinition of non-throwing operator new function ...
void* operator new(std::size_t count, std::nothrow_t const& tag) {
  std::cout << __PRETTY_FUNCTION__ << " nothrow | count: " << count << "\n";

  // handle zero-byte requests as one-byte requests
  count = (count == 0) ? 1 : count;
  void *ptr = std::malloc(count);

  return (ptr) ? ptr : nullptr;
}

// redefinition of (non-throwing) operator delete function ...
// this function will only be called when corresponding nothrow operator new
// function throws an exception ...
void operator delete(void *raw_memory, std::nothrow_t const& tag) noexcept {
  std::cout << __PRETTY_FUNCTION__ << " nothrow\n";

  // deallocate the memory
  // free does nothing if null pointer is being deleted
  free(raw_memory);
}

// this empty class is only used to test that the nothrow operator new
// function will not call nothrow operator delete but will always
// call the global operator delete - except if the nothrow operator new
// function throws an exception ...
struct Empty {
  Empty() {std::cout << "throw \"Throwing exception from Empty::Empty()\";" << "\n"; }
};

int main() {
  // new operator will call redefined ::operator new(size_t);
  int *pi = new int{10};
  *pi = 10;
  std::cout << "*pi: " << *pi << "\n";
  //delete pi;
  std::cout << "-------------------------------------------\n";

  // can call ::operator new(size_t) directly without using new operator ...
  pi = reinterpret_cast<int*>(::operator new(sizeof(int)));
  *pi = 4321;
  std::cout << "*pi: " << *pi << "\n";
  ::operator delete(pi); // can call ::op delete(pi) without using delete operator
  std::cout << "-------------------------------------------\n";

  // ::operator new[](size_t) will call redefined ::operator new(size_t)
  pi = new int [5] {11, 12, 13, 14, 15}; 
  std::cout << "pi[]: {" << pi[0] << ", " << pi[1] << ", " << pi[2] << ", " << pi[3] << ", " << pi[4] << "}\n";
  // ::operator delete[](void*) will call ::operator delete(void*)
  delete [] pi;
  std::cout << "-------------------------------------------\n";

  // Str::Str(char const*) has new expression which will call redefined ::operator new(size_t)
  Str s0{"quick as a fox"};
  std::cout << "s0: " << s0 << " | s0.size(): " << s0.size() << "\n";
  // corresponding ::operator delete(ptr) is not called until Str::~Str() is invoked ...
  std::cout << "-------------------------------------------\n";

  // you can't explicitly make calls to nothrow operator delete ...
  // only the nothrow operator new can call this function if the
  // corresponding ctor throws an exception ...
  // here's a scenario that will create the circumsntances that will ensure
  // the nothrow operator new will call nothrow operator delete function ...
  // obviously, this will only work for types with ctors and cannot be
  // tested for built-in types
  try {
    Empty *pe = new (std::nothrow) Empty{};
    delete pe;
  } catch (char const *ex) {
    std::cout << ex << "\n";
  }
  std::cout << "-------------------------------------------\n";

  // there is no overload for ::operator new[] (size_t, const nothrow_t&)
  // so it will call ::operator new(size_t)
  pi = new (std::nothrow) int [5] {101, 102, 103};
  if (pi) {
    std::cout << "pi[]: {" << pi[0] << ", " << pi[1] << ", " << pi[2] << ", " << pi[3] << ", " << pi[4] << "}\n";
    // there is no overload for ::operator delete[](void*, const nothrow_t&)
    // so it will call ::operator delete (void*)
    delete [] pi;
  }
  std::cout << "-------------------------------------------\n";

  // should return nullptr rather than throwing exception of type bad_alloc
  pi = new (std::nothrow) int [1'000'000'000'000ul];
  if (!pi) {
    std::cout << "unable to allocate a humongous memory chunk!!!\n";
  }
  std::cout << "-------------------------------------------\n";

  // illustrating placement operator new
  // begin by grabbing a sufficient amount of raw memory
#if 0 // your choice: use heap or stack memory for placement new
  void *proxy_int = ::operator new (sizeof(int));
#else
  int proxy_int[0x0010];
#endif
  // now construct an int at pre-allocated address - this will call
  // ::operator new(std::size_t, void*);
  // note that this specific ::operator new overload must not be redefined
  // by programmer ...
  int *test_ptr_int = new (proxy_int) int {1234}; // ::operator new(sizeof(int), proxy_int)
  std::cout << "*test_ptr_int: " << *test_ptr_int << " | " << proxy_int[0] << "\n";
  // now delete memory by explicitly calling placement delete ...
  ::operator delete(test_ptr_int, proxy_int);
  test_ptr_int = new (proxy_int+1) int {2143};
  std::cout << "*test_ptr_int: " << *test_ptr_int << " | "
            << proxy_int[0] << " | " << proxy_int[1] << "\n";
  ::operator delete(test_ptr_int, proxy_int);

#if 0
  // delete place memory
  ::operator delete (proxy_int);
#endif
  std::cout << "-------------------------------------------\n";
}

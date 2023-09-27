// CSD2125/CS225 10/25
// Customizing deletion callback
// Here, we're allocating memory to create objects of type Fred using
// placement new. If we don't provide a custom deleter, unique_ptr
// will return the memory pointed to by its encapsulated raw pointer
// using delete operator.
// To avoid the resulting program crash, we provide a custom deleter
// to unique_ptr that explicitly calls the dtor for the placement new
// constructed Fred object.
// The deleter is of type Fred_Deleter which is nothing but a functor
// [that is, overloads operator()] that explicitly calls the dtor for
// the object of type Fred. When the unique_ptr object encapsulating
// a pointer to type Fred goes out of scope, the functor will be called
// by the dtor of object of type unique_ptr<Fred, Fred_Deleter>.
// This code is proof-of-concept that a smart pointer of type unique_ptr
// can be integrated with a custom memory pool manager.

#include <memory>
#include <iostream>

// just a generic class definition with printing to text to stdcout
// to track construction/destruction process.
struct Fred {
  int f;
  Fred(int p = 0) : f{p} { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  ~Fred() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
  int F() const { return f; }
};

// class that overloads function call operator that explicitly calls
// ~Fred() thro' the raw pointer encapsulated by unique_ptr<Fred>
struct Fred_Deleter {
  void operator()(Fred *pf) const {
    pf->~Fred();
  }
};

int main() {
  // allocate memory on stack for 100 Fred objects
  int arena[100];
  
  // placement new to define a Fred object in memory pool arena ...
  std::unique_ptr<Fred, Fred_Deleter> uf { new (static_cast<void*>(arena)) Fred(44), Fred_Deleter()};
  std::cout << uf->F() << "\n";

  // when object uf goes out of scope, dtor of unique_ptr<Fred, Fred_Deleter>
  // will be invoked which will in turn will call Fred_Deleter::operator()(arena)
}

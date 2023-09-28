/*
CSD2125 10/11
new-delete-class.cpp
Besides letting programs replace some of the global operators new,
C++ also lets classes provide their own class-specific versions.

Compile/link: g++ -std=c++17 new-delete-classes.cpp -o ndc.out
*/
#include <iostream>
#include <new>
#include <cstdlib>

class X {
public:
  void* operator new(size_t);                                  // 1
  void* operator new(size_t, std::nothrow_t const &) noexcept; // 2
  void* operator new(size_t, void*);                           // 3

  void operator delete(void*) noexcept;                        // 4
  void operator delete(void*, std::nothrow_t const&) noexcept; // 5
  void operator delete(void*, void*) noexcept;                 // 6

  void* operator new[](size_t);                                 // 7
  void* operator new[](size_t, std::nothrow_t const&) noexcept; // 8
  void* operator new[](size_t, void*);                          // 9

  void operator delete[](void*) noexcept;                        // 10
  void operator delete[](void*, std::nothrow_t const&) noexcept; // 11
  void operator delete[](void*, void*) noexcept;                 // 12

  X(int x=11) : i{x} {}
  int I() const { return i; }
  void I(int const& x) { i = x; }

private:
  int i;
};

void* X::operator new(std::size_t size) {
  std::cout << "1: " << __PRETTY_FUNCTION__ << "\n";
  return std::malloc(size);
}

void* X::operator new(std::size_t size, std::nothrow_t const&) noexcept {
  std::cout << "2: " << __PRETTY_FUNCTION__ << "\n";
  return std::malloc(size); 
}

void* X::operator new(std::size_t size, void *inplace) {
  std::cout << "3: " << __PRETTY_FUNCTION__ << "\n";
  return inplace;
}

void X::operator delete(void *memory) noexcept {
  std::cout << "4: " << __PRETTY_FUNCTION__ << "\n";
  std::free(memory);
}

void X::operator delete(void *memory, std::nothrow_t const&) noexcept {
  std::cout << "5: " << __PRETTY_FUNCTION__ << "\n";
  std::free(memory);
}

void X::operator delete(void *, void *) noexcept {
  std::cout << "6: " << __PRETTY_FUNCTION__ << "\n";
  // nothing to do ...
  return;
}

void* X::operator new[](std::size_t size) {
  std::cout << "7: " << __PRETTY_FUNCTION__ << "\n";
  return std::malloc(size);
}

void* X::operator new[](std::size_t size, std::nothrow_t const&) noexcept {
  std::cout << "8: " << __PRETTY_FUNCTION__ << "\n";
  return std::malloc(size); 
}

void* X::operator new[](std::size_t size, void *inplace) {
  std::cout << "9: " << __PRETTY_FUNCTION__ << "\n";
  return inplace;
}

void X::operator delete[](void *memory) noexcept {
  std::cout << "10: " << __PRETTY_FUNCTION__ << "\n";
  std::free(memory);
}

void X::operator delete[](void *memory, std::nothrow_t const&) noexcept {
  std::cout << "11: " << __PRETTY_FUNCTION__ << "\n";
  std::free(memory);
}

void X::operator delete[](void *, void *) noexcept {
  std::cout << "12: " << __PRETTY_FUNCTION__ << "\n";
  // nothing to do ...
  return;
}

int main() {
  X *p1 = new X(10);                            // calls 1
  std::cout << "p1->i: " << p1->I() << "\n";
  delete p1;                                    // calls 4
  X *p2 = new (std::nothrow) X{11};             // calls 2
  std::cout << "p2->i: " << p2->I() << "\n";
  // delete p2; // doesn't call X::operator delete (p2, std::nothrow)
  X::operator delete (p2, std::nothrow);       // calls 5

  int arena[1000];
  
  //X *p3 = new (arena) X(111);                 // calls 3
  X *p3 = reinterpret_cast<X*>(X::operator new(sizeof(int), arena)); // calls 3
  p3->I(111);
  std::cout << "p3->i: " << p3->I() << "\n";
  X::operator delete(p3, arena);                // calls 6

  X *pa1 = new X [3] {1, 2, 3}; // calls 7
  std::cout << "pa1[]: <" << pa1[0].I() << ", " << pa1[1].I() << ", " << pa1[2].I() << ">\n";
  delete [] pa1;               // calls 10

  X *pa2 = new (std::nothrow) X[3] {11, 12, 13}; // calls 8
  std::cout << "pa2[]: <" << pa2[0].I() << ", " << pa2[1].I() << ", " << pa2[2].I() << ">\n";
  // delete [] pa2; // doesn't call X::operator delete[] (pa2, std::nothrow)
  X::operator delete[](pa2, std::nothrow);       // calls 11

  X *pa3 = new (arena) X [3] {21, 22, 23}; // calls 9
  std::cout << "pa3[]: <" << pa3[0].I() << ", " << pa3[1].I() << ", " << pa3[2].I() << ">\n";
  X::operator delete[](pa3, arena);        // calls 12
}

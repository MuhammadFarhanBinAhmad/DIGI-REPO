// allocator.cpp
// -- standard allocator
// csd2125 10/14
// compile/link: g++ -std=c++17 str.cpp allocator.cpp

#include <memory>
#include <new>
#include <algorithm>
#include <iostream>
#include <vector>
#include "str.h"

struct Fred {
  int x, y;
  Fred(int a=-1, int b=-1): x(a), y(b) { }
  ~Fred() { x = y = -2; }
};

struct Print {
  void operator()(Fred const& f) {
    std::cout << '(' << f.x << ',' << f.y << ')';
  }
  void operator()(double x) {
    std::cout << x << ' ';
  }
  void operator()(int x) {
    std::cout << x << ' ';
  }
};

int main() {
  Print prnt;
  
  // usual calls to new[] and delete[] operators
  Fred *fredA = new Fred[5];
  std::cout << "fredA: " << fredA << "\n";
  std::for_each(fredA, fredA+5, prnt);
  std::cout << "\n";
  delete[] fredA;

  // we can make it hard on ourselves by using global
  // operator new[] and operator delete[] functions from <new>
  fredA = reinterpret_cast<Fred*>(::operator new[](sizeof(Fred)*5));
  std::cout << "fredA: " << fredA << "\n";
  for (int i{}; i < 5; ++i) {
    new (fredA+i) Fred(i,2*i);
  }
  std::for_each(fredA, fredA+5, prnt);
  std::cout << "\n";
  for (int i{4}; i >= 0; --i) {
    fredA[i].~Fred();
  }
  ::operator delete[](fredA);
  fredA = nullptr;

  // allocators are handle classes that do the work of allocating
  // raw memory and then constructing that raw memory. Similarly,
  // they separate destruction and deallocation of memory.
  std::allocator<Fred> fred_alloc;
  try {
    fredA = fred_alloc.allocate(5);
    std::cout << "fredA: " << fredA << "\n";
  } catch (std::bad_alloc) {
    std::cout << "not enough memory" << std::endl;
    return 1;
  }
  // not good - Fred objects are not yet constructed!!!
  // comment next line to remove valgrind errors
  std::for_each(fredA, fredA+5, prnt);
  // better ...
  for (int i{}; i < 5; ++i) {
    fred_alloc.construct(fredA+i,2*i,2*i+1);
  }
  std::for_each(fredA, fredA+5, prnt);
  std::cout << "\n";

  // make sure to destruct in reverse order of allocation ...
  for (int i{4}; i >= 0; --i) {
    fred_alloc.destroy(fredA+i);
  }
  std::for_each(fredA,fredA+5,prnt);
  fred_alloc.deallocate(fredA,5);
  std::cout << "\n\n";

  // algorithms to copy and fill uninitialized memory
  std::vector<Str> vs{"t", "o", "d", "a", "y"};
  std::allocator<Str> str_alloc;
  // allocate twice as many elements as vs holds
  Str *ps = str_alloc.allocate(vs.size()*2);
  // construct elements starting at ps as copies of elements in vs
  Str *ps2 = std::uninitialized_copy(vs.begin(), vs.end(), ps);
  // initialize the remaining elements as "z"
  std::uninitialized_fill_n(ps2, vs.size(), Str{"z"});

  // Part of the allocator structure is a member template called rebind<>.
  // This template structure provides the ability for any allocator to allocate
  // storage of another type indirectly.
  // If MyAlloc is an allocator type, then MyAlloc::rebind<T2>::other
  // is the type of the same allocator specialized for elements of type T2.
  // You use rebind<> if you implement a container and have to allocate
  // memory for a type that differs from the element's type. For example,
  // to implement a deque, you typically need memory for arrays that manage
  // blocks of elements. Thus, you need an allocator to allocate arrays
  // of pointers to elements.
  std::allocator<Fred>::rebind<double>::other double_alloc;
  double *doubleA = double_alloc.allocate(3);
  // not good - double objects are not yet constructed!!!
  // comment next line to remove valgrind errors
  std::for_each(doubleA, doubleA+3, prnt);
  std::cout << "\n";
  for (int i{}; i < 3; ++i) {
    double_alloc.construct(doubleA+i, double(i));
  }
  std::for_each(doubleA, doubleA+3, prnt);
  std::cout << "\n";
  double_alloc.deallocate(doubleA, 3);

  // it is possible to get a handle to a container's allocator ...

  // allocate an array with space for 5 elements using vector's allocator:
  std::vector<int> vi;
  int *pi = vi.get_allocator().allocate(5);
  std::cout << "vi size: " << vi.size() << " | capacity: " << vi.capacity() << "\n";

  // construct values in-place on the array:
  for (int i{}; i < 5; ++i) {
    vi.get_allocator().construct(pi+i, i*2);
  }
  std::for_each(pi, pi+5, prnt);
  std::cout << '\n';

  // destroy and deallocate:
  for (int i{4}; i >= 0; --i) {
    vi.get_allocator().destroy(pi+i);
  }
  vi.get_allocator().deallocate(pi, 5);
}

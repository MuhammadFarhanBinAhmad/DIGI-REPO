/*
CSD2125: 10/11/2021
mempool.cpp
This class illustrates objects of type X using a linear memory pool
owned by objects of type MemPool. The MemPool class keeps track of
the various MemPools in use by the application in the form of a
stack so that MemPools can be deleted in the reverse order of
their creation.
Additional note: Objects of type X don't actually delete their
memory - they are deleted only when their MemPool is deleted.

Compile: g++ -std=c++17 mempool.cpp
*/
#include <cstddef>
#include <new>
#include <iostream>
 
// This class provides a global stack of memory pools.
// Since C++ deletes objects in reverse-order in which they are constructed,
// the pools must be destructed in reverse order of construction ...
class MemPool {
public:
  MemPool(std::size_t sz);
  ~MemPool();
  MemPool(MemPool const&) = delete; // no copies
  MemPool& operator=(MemPool const&) = delete; // no copies

  // allocate from pool sz bytes aligned at align_value
  void* allocate(std::size_t sz, std::size_t align_value);

  // return pointer to current (most recent) MemPool ...
  static MemPool& current() { return *ptr_to_current_mempool; }

private:
  // range of addresses for pool: [start, end) with free pointing
  // to next free location ...
  char *start, *free, *end; // char* instead of void* enables pointer arithmetic
  // keep track of stack of MemPools
  MemPool *ptr_to_prev_mempool;
  static MemPool *ptr_to_current_mempool;
};
 
MemPool* MemPool::ptr_to_current_mempool {nullptr};
 
MemPool::MemPool(std::size_t size):
  start{static_cast<char*>(::operator new(size))}, free{start}, end{start + size} {
  ptr_to_prev_mempool = ptr_to_current_mempool;
  ptr_to_current_mempool = this;
}
 
MemPool::~MemPool() {
  ::operator delete(start);
  ptr_to_current_mempool = ptr_to_prev_mempool;
}
 
void* MemPool::allocate(std::size_t size, std::size_t align_value) {
  // take care of 0-sized memory requests ...
  size = (size == 0) ? 1 : size;

  // align the pointer to match align_value
  std::size_t bytes_to_align = (free - start) % align_value;
  bytes_to_align = (bytes_to_align) ? align_value - bytes_to_align : bytes_to_align;
 
  // test if we can still allocate that much memory
  if (end - free < size + bytes_to_align) {
    throw std::bad_alloc();
  }

  // return value of aligned addresss
  char *returnable_memory = free + bytes_to_align;
  // free memory now starts after newly allocated object
  free = returnable_memory + size;
  return returnable_memory;
}
 
// objects of type X uses a specific allocation/deallocation mechanism:
// they acquire memory from the MemPool but they don't deallocate - they 
// instead rely on the MemPool to return their memory ...
struct X {
  int m=-111;
  X(int rhs=-111) : m{rhs} { std::cout << __PRETTY_FUNCTION__ << "\n";}
  int M() const { return m; }

  void* operator new(std::size_t);
  //void* operator new[](std::size_t);
  void  operator delete(void*) {} // don't deallocate memory for single objects
};
 
void* X::operator new(std::size_t size) {
  std::cout << __PRETTY_FUNCTION__ << " | size: " << size << "\n";
  // C++11 offers a portable way to find out alignment
  return MemPool::current().allocate(size, alignof(X));
}

#if 0
void* X::operator new[](std::size_t size) {
  std::cout << __PRETTY_FUNCTION__ << " | size: " << size << "\n";
  // C++11 offers a portable way to find out alignment
  return X::operator new(size);
}
#endif

// driver program
int main() {
  MemPool first_pool(3*sizeof(X));
  X *p1 = new X(11); // uses the allocator function defined above
  X *p2 = new X(12);
  X *p3 = new X(13);
  std::cout << "<" << p1->M() << ", " << p2->M() << ", " << p3->M() << ">\n";
  delete p3; // doesn't really deallocate the memory because operator delete has an empty body
 
  try {
    X *p4 = new X{222}; // should fail
  } catch(...) {
    std::cout << "exception thrown!!!\n";
  }

  // uses global array allocation routine because we didn't 
  // provide operator new[] and operator delete[]
  /*
  Remember how name lookup works: In brief, the compiler starts in the current
  scope (here, in X's scope), and looks for the desired name (here, operator new[]);
  if no instances of the name are found, it moves outward to the next enclosing scope
  (in global scope) and repeats. Once it find a scope containing at least one instance
  of the name (in this case, global scope), it stops looking and works only with the
  matches it has found, which means that further outer scopes (in this case, the global
  scope) are not considered and any functions in them are hidden; instead, the compiler
  looks at all the instances of the name it has found, selects a function using overload
  resolution, and finally checks access rules to determine whether the selected function
  can be called. The outer scopes are ignored even if none of the overloads found has a
  compatible signature, meaning that none of them could possibly be the right one; the
  outer scopes are also ignored even if the signature-compatible function that's selected
  isn't accessible. That's why name hiding works the way it does in C++. 
  */
  constexpr int x_size{10};
  X *p5 = new X[x_size]; 
  for (int i{0}; i < x_size; ++i) {
    std::cout << p5[i].M() << " ";
  }
  std::cout << "\n";
  delete[] p5; // global array deallocation
 
  MemPool *ptr_second_pool = new MemPool(1000); // a large MemPool
  X *p6 = new X(111); // allocate a new object from that MemPool
  X *p7 = new X(222);
  std::cout << "<" << p6->M() << ", " << p7->M() << ">\n";
  delete ptr_second_pool; // also deallocates the memory for p6 and p7
 
} // Here first_pool goes out of scope, deallocating the memory for p1, p2 and p3

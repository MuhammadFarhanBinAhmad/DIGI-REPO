/*
CSD2125 10/11
debug.cpp
This source file shows how to debug memory problems by redefining
global placement operator new and operator delete functions.
*/
#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>

// header to prefix every memory allocation ...
struct MemoryHeader {
  char file_name[80]{};
  int  line_numb{-1};
};

void* operator new(size_t size, char const *filename, int line) {
  size_t total_size = size + sizeof(MemoryHeader), aligned_size{total_size};
  if (total_size % __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
    aligned_size = (total_size/__STDCPP_DEFAULT_NEW_ALIGNMENT__+1)*__STDCPP_DEFAULT_NEW_ALIGNMENT__;
  } 
  void *raw_memory { std::malloc(aligned_size) };
  MemoryHeader *pmh {reinterpret_cast<MemoryHeader*>(raw_memory)};
  std::strcpy(pmh->file_name, filename);
  pmh->line_numb = line;

  std::cout << "Allocating memory in "
            <<  pmh->file_name << " at line number " << pmh->line_numb << std::endl;
  return static_cast<void*>(static_cast<char*>(raw_memory)+sizeof(MemoryHeader));
}

void operator delete(void *raw_memory, char const *, int) noexcept {
  char *raw_memory_start {reinterpret_cast<char*>(raw_memory) - sizeof(MemoryHeader)};
  MemoryHeader *pmh {reinterpret_cast<MemoryHeader*>(raw_memory_start)};
  std::cout << "Deleting memory allocated in "
            << pmh->file_name << " at line number " << pmh->line_numb << std::endl;
  free(raw_memory_start);
}

struct C {
  int value{1};
};

int main() {
  //int *pi {new (__FILE__, __LINE__) int {11}}; // new operator ...
  int *pi = reinterpret_cast<int*>(::operator new (sizeof(int), __FILE__, __LINE__));
  *pi = 11;
  std::cout << "value of *pi: " << *pi << "\n";
  ::operator delete (pi, __FILE__, __LINE__); // ::operator delete(void*)

  C *pc{new (__FILE__, __LINE__) C};
  ::operator delete (pc, __FILE__, __LINE__);
}

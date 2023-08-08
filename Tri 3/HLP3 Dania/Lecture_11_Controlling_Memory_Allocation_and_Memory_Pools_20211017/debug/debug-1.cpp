/*
CSD2125 10/11
debug-1.cpp
This source file shows how to debug memory problems by redefining
placement operator new and operator delete functions. Here,
we're writing placement new and delete functions as member functions.
*/
#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>

struct MemoryHeader {
  char file_name[80]{};
  int  line_numb{-1};
};

class C {
private:
  int value{1};
public:
  void* operator new(size_t size, char const *filename, int line) {
    size_t total_size = size + sizeof(MemoryHeader), aligned_size{total_size};
    if (total_size % __STDCPP_DEFAULT_NEW_ALIGNMENT__) {
      aligned_size = (total_size/__STDCPP_DEFAULT_NEW_ALIGNMENT__+1)*__STDCPP_DEFAULT_NEW_ALIGNMENT__;
    } 
    void *raw_memory { std::malloc(aligned_size) };

    MemoryHeader *pmh {reinterpret_cast<MemoryHeader*>(raw_memory)};
    std::strcpy(pmh->file_name, filename);
    pmh->line_numb = line;
    return static_cast<void*>(static_cast<char*>(raw_memory)+sizeof(MemoryHeader));
  }

  void operator delete(void *raw_memory, char const *filename, int line) noexcept {
    char *raw_memory_start {reinterpret_cast<char*>(raw_memory) - sizeof(MemoryHeader)};
    int *raw_memory_int = reinterpret_cast<int*>(raw_memory_start);
    MemoryHeader *pmh {reinterpret_cast<MemoryHeader*>(raw_memory_start)};
    std::cout << "Deleting memory allocated from: "
              << pmh->file_name << ":" << pmh->line_numb << std::endl;
    free(raw_memory_start);
  }
};

int main() {
  //C *pc {new (__FILE__, __LINE__) C};
  

  C *pc = reinterpret_cast<C*>(C::operator new (sizeof(C), __FILE__, __LINE__));
  C::operator delete(pc, __FILE__, __LINE__);
}

// HLP3: 09/09/2020
// alignment.cpp: Specifying alignment of structure and class objects and their
// data members on specific byte boundaries using C++11 alignas type specifier
// and C++11 alignof operator

#include <iostream>
#include <cstdint>
#include <new>

// only way to align structure and class objects before C++11 was
// to inject padding
// here we align the following structure at 16 byte boundaries:
const uint32_t AlignAt {16U};
struct PreCpp11 {
  int32_t i;
  uint8_t pad[AlignAt-sizeof(int32_t)];
};

// some examples where we change the natural alignment using 
// the alignas specifier and alignof operator ...
struct Empty {};
struct alignas(32) Empty32 {};
struct SAC { char ch[8]; };
struct alignas(alignof(long double)) SALD { char ch[8]; };

// Embedded environments, kernel, drivers, game development and other areas
// might require a non-default alignment for memory allocations. Complying
// those requirements might improve the performance or satisfy some hardware
// interface. For example, to perform geometric data processing using SIMD
// instructions, you might need 32-byte alignment for a structure that
// holds coordinates for a 3D position:
struct alignas(32) Pos3d {
  double x, y, z;
};

// Pos3d has three data members of type double, and objects of this type
// have natural alignment of 8 bytes. Using alignas specifier, we've changed
// the alignment to 32 bytes.

// C++11/14 provide no guarantee how memory will be dynamically aligned
// for objects of type Pos3d.
// C++17 fixes that hole by introducing new memory allocation overheads
// for new and delete with align_val_t parameter:
// void* operator new(size_t, align_val_t);
// void operator delete(void*, size_t, align_val_t);

// The standard also defines macro __STDCPP_DEFAULT_NEW_ALIGNMENT__ to
// specify the default alignment for dynamic memory allocations. Most
// compilers specify this macro to be 16.
// If the alignment for Pos3d is larger than __STDCPP_DEFAULT_NEW_ALIGNMENT__
// the compiler will choose overloads of operator new and operator delete
// with align_val_t parameter.
// We can provide custom implementations of these operator new and
// operator delete functions:
void* operator new(std::size_t size, std::align_val_t align) {
  void *ptr = std::aligned_alloc(static_cast<std::size_t>(align), size);
  if (!ptr) throw std::bad_alloc{};
  std::cout << "new: " << size << ", align: " << static_cast<std::size_t>(align)
            << ", ptr: " << ptr << '\n';
  return ptr;
}

void operator delete(void *ptr, std::size_t size, std::align_val_t align) noexcept {
  std::cout << "delete: " << size << ", align: " << static_cast<std::size_t>(align)
            << ", ptr: " << ptr << '\n';
  std::free(ptr);
}

int main() {
  PreCpp11 p1;
  bool flag = reinterpret_cast<size_t>(&p1) % 16;
  std::cout << "p1 is " << (flag ? "not " : "") << "aligned at 16 byte boundary\n";

  std::cout << "Objects of type Pos3d are aligned at " << alignof(Pos3d) << " bytes\n";
  std::cout << "Objects of type Pos3d require " << sizeof(Pos3d) << " storage bytes\n";

  // dynamically allocated objects of type Pos3d will have same alignment
  Pos3d *p = new Pos3d;
  std::cout << p << "\n";
  delete p;

  std::cout << "sizeof(Empty): " << sizeof(Empty) << " | alignof(Empty): " << alignof(Empty) << "\n";
  std::cout << "sizeof(Empty32): " << sizeof(Empty32) << " | alignof(Empty32): " << alignof(Empty32) << "\n";
  std::cout << "sizeof(SAC): " << sizeof(SAC) << " | alignof(SAC): " << alignof(SAC) << "\n";
  std::cout << "sizeof(SALD): " << sizeof(SALD) << " | alignof(SALD): " << alignof(SALD) << "\n";
}

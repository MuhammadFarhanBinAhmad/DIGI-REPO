// HLP2: exhaust.cpp
// 01/18/2022
// Program to illustrate how the runtime environment throws a std::bad_alloc
// exception upon free store memory exhaustion. The exception is thrown when
// new or new[] operators are unable to allocate the block of requested memory.
// The program also illustrates the nothrow version of the new[] operator
// Note: Exceptions will be covered in 2nd half of trimester and you're not
// expected to know about them for the midterm test.

#include <iostream> // std::cout
#include <new>      // std::bad_alloc

int main() {
  // the try block is required if you want your code to be inspected
  // by the C++ runtime exception mechanism 
  try {
    // exhaust memory by constantly allocating memory without deleting memory
    int count = 1;
    while (1) {
      // ask for an humongous amount of memory ...
      int *pi = new int [1'000'000'000ul];

      // however, if new[] throws std::bad_alloc exception, program execution will
      // not reach the next statement ...
      // instead, code execution will jump to an appropriate catch clause.
      // if there's no appropriate catch clause, the runtime environment will
      // abort your program ...

      // just as in C-style programs, let's check [in vain] if memory request was
      // satisfied by testing pi with nullptr ...
      if (pi) {
        std::cout << "count==" << count++ << '\n';
      } else { // code execution will never reach here ...
        std::cout << "Unable to allocate humongous memory!!!\n";
      }
    }
  } catch (std::bad_alloc const& e) {
    // this catch block catches the exception thrown by new[]
    // we just print the error message and move on ...
    std::cout << "Exception thrown: " << e.what() << "\n";
  }

  // now, program execution continues as before ...
  // let's allocate a small array ...
  int *pi = new int [5] {31, 32, 33, 34, 35};
  // print the values ...
  for (int i{}; i < 5; ++i) {
    std::cout << pi[i] << ' ';
  }
  std::cout << "\n";

  // return the memory back to the free store ...
  delete [] pi;

  // now, let's use the nothrow version of new[] that allows us to
  // use the traditional C-style way of checking for nullptr ...
  // again exhaust free store memory by continually allocating without
  // corresponding deallocation ...
  int count = 1;
  while (true) {
    int *pi2 = new (std::nothrow) int [100'000'000ul] {41,42,43,44,45};
    if (pi2 != nullptr) {
      std::cout << count++ << ": Memory allocated!!!\n";
    } else {
      std::cout << "Memory allocation failed!!! Terminate program\n";
      return 1;
    }
  }
}

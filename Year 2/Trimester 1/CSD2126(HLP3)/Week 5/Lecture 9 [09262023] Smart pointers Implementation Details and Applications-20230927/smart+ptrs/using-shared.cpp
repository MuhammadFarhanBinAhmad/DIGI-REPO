// CSD2125 10/11
// using-shared.cpp
// Illustrates usage of std::shared_ptr<T> smart pointer in conjunction with
// std::make_shared
#include <memory>
#include <iostream>

int main() {
  // a shared_ptr can be defined in a similar way to unique_ptr
  std::shared_ptr<double> sd1 {new double{9.9}};
  // you can also dereference it to access what it points to or
  // change the value stored at the address:
  std::cout << "*sd1: " << *sd1 << " | sd1: " << sd1 << "\n";
  *sd1 += 2.2;
  std::cout << "*sd1: " << *sd1 << " | sd1: " << sd1 << "\n";

  // creating a shared_ptr<T> object involves a more complicated process than
  // creating a unique_ptr<T>, not least because of the need to maintain a
  // reference count. The definition of sd1 involves one memory allocation
  // for the double object and another allocation relating to the smart pointer
  // object. Allocating memory in the free store is expensive on time. You can
  // make the process more efficient by using the std::make_shared<T>(...)
  // function [defined in <memory>] to create a smart pointer of type
  // shared_ptr<T>:
  std::shared_ptr<double> sd2 { std::make_shared<double>(11.6) };

  // we can initialize a shared_ptr<T> with another causing the reference
  // count to be incremented
  std::shared_ptr<double> sd3 {sd2};
  std::cout << "sd1.use_count: " << sd1.use_count() << " | sd2.use_count: "
            << sd2.use_count() << " | sd3.use_count: " << sd3.use_count() << "\n";
  
  sd3 = sd1;
  std::cout << "sd1.use_count: " << sd1.use_count() << " | sd2.use_count: "
            << sd2.use_count() << " | sd3.use_count: " << sd3.use_count() << "\n";

  // starting with C++20, you can also use make_shared<T[]>() to ensure a
  // a shared_ptr<T[]> that holds the address of a newly created array in the
  // free store:
  // note: this compiles in g++17 ...
  std::shared_ptr<bool[]> sbs{ std::make_shared<bool[]>(5) };
  for (int i{}; i < 5; ++i) {
    sbs[i] = (i%2) ? true : false;
  }
  std::cout << "sbs.use_count: " << sbs.use_count() << "\n";

  // better option is to store the address of an array<T> or vector<T> container
  // object that you create in the free store ...
  // see sharedptr-cont.cpp for an example ...
}

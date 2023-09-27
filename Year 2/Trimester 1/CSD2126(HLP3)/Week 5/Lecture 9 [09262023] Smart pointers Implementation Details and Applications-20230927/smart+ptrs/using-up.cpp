// CSD2125/CS225 10/25
// Usage of std::unique_ptr<T> smart pointer

#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>

template <typename T>
T incr(T param) {
  return param+static_cast<T>(1);
}

template <typename T>
T* incr_thru_ptr(T *param) {
  *param += static_cast<T>(1);
  return param;
}

int function_may_throw(int x) {
  if (x % 2) {
    throw(std::domain_error("throw an exception"));
  } else {
    return x+1;
  }
}

template <typename T>
void func(std::unique_ptr<T> const& param, int param2) {
  std::cout << "param: " << *param << " | param2: " << param2 << "\n";
}

// return is not by copy ctor but instead using move ctor ..
std::unique_ptr<std::string> string_factory(char const *cstr) {
  return std::unique_ptr<std::string>{std::make_unique<std::string>(cstr)};
}

// argument in caller must be rvalue reference enabling
// param to be initialized using move ctor ...
void pass_a_string(std::unique_ptr<std::string> param) {
  std::cout << __PRETTY_FUNCTION__ << " | param: " << *param << "\n";
}

class Int {
  int mi = 0;
  static int counter;
public:
  Int(int i) : mi{i} { ++counter; }
  ~Int() { --counter; std::cout << "Hasta Luego: " << mi << " | counter: " << counter << std::endl;  }
  operator int() const { return mi; }
};

int Int::counter = 0;

//---------------------------------------------------------------------------------
template <typename T>
void myswap(T& lhs, T& rhs) noexcept {
  T tmp = std::move(lhs);
  lhs = std::move(rhs);
  rhs = std::move(tmp);
}

// specialization of function template myswap for T=std::unique_ptr<T>
template <typename T, typename D>
void myswap(std::unique_ptr<T,D>& lhs, std::unique_ptr<T,D>& rhs) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  lhs.swap(rhs);
}

//---------------------------------------------------------------------------------
int main() {
  // in the really old days, you would define a raw pointer like this:
  double *p0 = new double {1.1};
  // it had many problems with respect to ownership [such as double-deletion, 
  // dangling pointers, memory leak, ... ]
#if 0
  double *p0_dup = p0;
  delete p0_dup;
  ++(*p0); // disastrous ...
#else
  delete p0;
#endif

// ------------------------------------------------------------------------------

  // in the not so old days, you had to create and initialize a unique_ptr<T> object like this:
  std::unique_ptr<double> pd0 { new double {9.9} };
  // this creates pd1, which contains the address of a double object in the free store
  // that is initialized with 9.9
  // the big difference is that you now longer have to worry about deleting the double
  // variable from the free store

// ------------------------------------------------------------------------------

  // while this syntax remains valid, the recommended way [since C++14] to create a
  // unique_ptr<> is by means of the std::make_unique() function template ...

  // std::make_unique<T>() creates a variable of type T that is value-initialized.
  // For built-in types, value-initialization means object is initialized to zero.
  std::unique_ptr<double> pd1 { std::make_unique<double>() };
  std::cout << "*pd1: " << *pd1 << "\n";

  std::unique_ptr<double> pd2 { std::make_unique<double>(11.1) };
  // the args to std::make_unique<T>(...) are exactly those values that would otherwise
  // appear in the braced initializer of a dynamic allocation of the form new T{...}

  // Why should you exclusively use std::make_unique<>(...) ...
  // consider the two seemingly equivalent calls:
  try {
    func(std::make_unique<std::string>("C++14"), function_may_throw(10));                 // 1
    func(std::unique_ptr<std::string>(new std::string("C++11")), function_may_throw(1)); // 2
  } catch (std::exception const& e) {
    std::cout << "catching an exception: " << e.what() << "\n";
  }

  // there is a potential memory leak in 2 for the following sequence of calls:
  // new string("C++11")
  // function_may_throw(12)
  // std::unique_ptr<std::string>(...)
  // on the other hand, std::make_unique<>(...) guarantees that no memory leak will cover

// ------------------------------------------------------------------------------

  // you can dereference pd1 and pd2 just like an ordinary pointer:
  *pd1 += *pd2;
  std::cout << "*pd1: " << *pd1 << "\n";
  
// ------------------------------------------------------------------------------

  // you can access the address stored inside a smart pointer by calling its get() function ...
  std::cout << pd1.get() << "\n";

  // this is dangerous ...
  double *pd1_dup = pd1.get(); // should never do this!!!
  std::cout << pd1_dup << "\n";
#if 0
  delete pd1_dup;
#endif

  // All smart pointers have a get() function that will return the address that the pointer contains.
  // You should only ever access the raw pointer inside a smart pointer to pass it to functions that
  // use this pointer briefly, never to functions or objects that would hang on to a copy of this pointer.
  std::cout << *incr_thru_ptr(pd1.get()) << "\n";
  std::cout << "*pd1: " << *pd1 << "\n";

// ------------------------------------------------------------------------------

  // Because a unique_ptr has exclusive ownership to the object being pointed to,
  // it doesn't support ordinary copy or assignment ...
  std::unique_ptr<int> pi1(std::make_unique<int>(2022));
  std::cout << "pi1: " << pi1.get() << "\n";
#if 0
  std::unique_ptr<int> pi2{pi1}; // no copy for unique_ptr
  std::unique_ptr<int> pi3;
  pi3 = pi1; // no copy-assignment for unique_ptr
#endif

// ------------------------------------------------------------------------------

  // although we can't copy or assign a unique_ptr, we can transfer ownership from
  // one unique_ptr to another by calling release or reset ...

  // transfers ownership from pi1 to pi2 with pi1 becoming null ...
  std::unique_ptr<int> pi2(pi1.release());
  std::cout << "pi1: " << pi1.get() << " | pi2: " << pi2.get() << "\n";
  
  std::unique_ptr<int> pi3(std::make_unique<int>(2023));
  std::cout << "pi3: " << pi3.get() << "\n";
  // transfers ownership from pi3 to pi2
  // memory of object pointed to by pi2 will be deleted ...
  pi2.reset(pi3.release());
  std::cout << "pi2: " << pi2.get() << " | pi3: " << pi3.get() << "\n";

  // ownership can also be transferred from a unique_ptr to a raw pointer ...
  int *pi4 = pi2.release();
  std::cout << "*pi4: " << *pi4 << "\n";
  delete pi4;

  // Be careful with release()!!!
  // pi2.release() without capturing the raw pointer that comes out will cause
  // a memory leak!!!
  // pi2.reset() will ensure the object's memory is returned to free store

//---------------------------------------------------------------------------

  // Even though unique_ptr<> cannot be copied or assigned, it can be
  // moved for rvalues ... 
  std::unique_ptr<std::string> ps1 = string_factory("hello");
  std::cout << "*ps1: " << *ps1 << "\n";

  // here we'd we passing by value [which is illegal] if we don't use std::move
  pass_a_string(std::move(ps1)); // how to get it to work???
  std::cout << "ps1: " << ps1.get() << "\n";

//---------------------------------------------------------------------------

  // experiments with user-defined type ...
  std::unique_ptr<Int> ip1{std::make_unique<Int>(100)};
  std::cout << "*ip1: " << *ip1 << " | ip1: " << ip1.get() << "\n";

  std::unique_ptr<Int> ip2{std::move(ip1)};
  std::cout << "*ip2: " << *ip2 << " | ip1: " << ip1.get() << " | ip2: " << ip2.get() << "\n";

  ip2.reset(new Int{200}); //std::make_unique<Int>(200));
  std::cout << "*ip2: " << *ip2 << " | ip2: " << ip2.get() << "\n";
  Int *raw_ip3 = ip2.release();
  std::cout << "*raw_ip3: " << *raw_ip3 << " | ip2: " << ip2.get() << "\n";

  std::unique_ptr<Int> ip4(std::make_unique<Int>(300)), ip5(std::make_unique<Int>(400));
  std::cout << "ip4: " << ip4.get() << " | ip5: " << ip5.get() << "\n"; 
  myswap(ip4, ip5); //std::swap(ip4, ip5);
  std::cout << "ip4: " << ip4.get() << " | ip5: " << ip5.get() << "\n"; 

}
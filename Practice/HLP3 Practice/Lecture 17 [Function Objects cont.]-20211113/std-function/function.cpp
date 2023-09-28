// CSD2125: 11/09
// Code to illustrate automatic type deduction that allows a function template
// to accept a callable (lambda, function object, function pointer) while a
// non-template function will take a function pointer or a function object
// but not a lambda
#include <iostream>
#include <vector>
#include <algorithm>

// function template to enumerate integer values from 0 up to N-1
// and provide each value to given callable f
template <typename F>
void for_upto(int N, F f) {
  for (int i{0}; i <= N; ++i) {
    f(i);
  }
}

// function template to print value t to standard output
template <typename T>
void print(T t) {
  std::cout << t << ' ';
}

// function object that prints values in multiples of x
class S {
public:
  S(int v=0) : x{v} {}
  void operator()(int v) const { std::cout << x*v << " "; }
private:
  int x;
};

// non-template function to enumerate integer values from 0 to N-1
// and provide each value to function pointer f
void for_upto2(int N, void (*f)(int)) {
  for (int i{0}; i != N; ++i) {
    f(i);
  }
}

int main() {
  // insert values from 0 to 4
  std::vector<int> values;
  for_upto(5, [&values](int i) {values.push_back(i); });
  
  // check if values were inserted into container values ...
  std::for_each(std::begin(values), std::end(values), [](int x) { std::cout << x << ' '; });
  std::cout << "\n";

  // print values from 0 to 40 in multiples of 10
  for_upto(5, S(10)); printf("\n");
  // print elements from 0 to 4
  for_upto(5, print<int>); printf("\n");

  for_upto2(5, print<int>); printf("\n");

  // while non-template function for_upto2 will work when passed 
  // function pointer print<int>, it will produce an error when
  // passed the lambda:
  //for_upto2(5, [&values](int i) { values.push_back(i); });
  
  // capture-less lambda will implicitly convert to function pointer ...
  for_upto2(5, +[](int i) { std::cout << i << " "; }); std::cout << "\n";
}

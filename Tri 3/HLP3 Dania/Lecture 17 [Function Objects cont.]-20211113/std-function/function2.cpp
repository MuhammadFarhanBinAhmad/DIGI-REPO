// CSD2125 11/09
// The standard library's class template std::function<> permits
// an alternative formulation of for_upto()
// The following source code also shows how to treat class member
// functions as function objects.
// C++ language rules prevent you from calling a class member function
// .length() member function of std::string as if it were a non-member
// function (std::string::length(str)), and because of that you
// don't consider data members and member functions to be function objects.
// But if you store them in a std::function<> object, you can call it with
// a normal call syntax. See function foo for this.
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

// The template argument to std::function<> is a function type that describes
// the parameter types the function object will receive and the return type
// that it should produce, much like a function pointer describes the
// parameter and result types.
void for_upto(int N, std::function<void(int)> f) {
  for (int i{0}; i != N; ++i) { f(i); }
}

// a function template ...
template <typename T>
void print(T t) {
  std::cout << t << ' ';
}

// a function object ...
class S {
public:
  S(int v=0) : x{v} {}
  void operator()(int v) const { std::cout << v*x << ' '; }
private:
  int x;
};

void foo();

int main() {
  // call with capture lambda ...
  std::vector<int> values;
  for_upto(5, [&values](int x) { values.push_back(x); });
  std::for_each(std::begin(values), std::end(values),
                [](int x) { std::cout << x << ' '; });
  std::cout << "\n";

  // call with function pointer ...
  for_upto(5, print<int>); std::cout << "\n";

  // call with function object ...
  for_upto(5, S(5)); std::cout << "\n";

  auto tmp = std::multiplies<>();
  std::cout << "2 * 5: " << std::multiplies<>()(2, 5) << "\n";

  foo();
}

class C {
public:
  int func(int x, int y) const { return x*y; }
};

void foo() {
  std::vector<std::function<float(float,float)>> tasks;
  tasks.push_back(std::fmaxf); // plain function
  tasks.push_back(std::multiplies<float>()); // function object
  tasks.push_back(std::multiplies<>()); // generic call operator

  float x = 1.1f;
  tasks.push_back([x](float a, float b) { return a*x+b; }); // lambda
  tasks.push_back([x](auto a, auto b) { return a*x+b; }); // generic lambda

  for (std::function<float(float, float)> f : tasks) {
    std::cout << f(10.1, 11.1) << "\n";
  }

  // C++ language rules prevent you from calling a class member function
  // .length() member function of std::string as if it were a non-member
  // function (std::string::length(str)), and because of that you
  // don't consider data members and member functions to be function objects.
  // But if you store them in a std::function<> object, you can call it with
  // a normal call syntax
  std::string str {"C++: terror or horror"};
  std::function<std::string::size_type(std::string&)> f; // notice the std::string& parameter
  f = &std::string::length;
  std::cout << f(str);

  // calling a member function from a home-grown class C
  std::function<int(C const&, int,int)> mf; // notice the C const& parameter
  mf = &C::func;
  std::cout << mf(C(), 10, 20) << "\n";
}
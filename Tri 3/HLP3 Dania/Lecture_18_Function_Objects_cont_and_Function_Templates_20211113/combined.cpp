// CSD2125: 11/11
// We showcase function composition using lambdas.
// We'll use this example next week to look at variadic templates.
#include <iostream>
#include <functional>

#if 0
template <typename F, typename G, typename H>
auto concat(F f, G g, H h) {
  return [=](auto x, auto y) { return f(g(h(x, y))); };
}
#else
template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts) {
  if constexpr (sizeof...(ts) > 0) {
    return [=](auto ...parameters) { return t(concat(ts...)(parameters...)); };
  } else  {
    return t;
  }
}
#endif

// f(g(h(x, y)))
int main() {
  auto f {[] (int i) { return i * 2; }};
  auto g {[] (int i) { return i * 3; }};
  using h = std::plus<int>;

  // instantiate function template with template arguments specified
  // by types of lambdas f, g, and function object h
  auto combined (concat(f, g, h()));
  // call composed function ...
  std::cout << combined(3, 4) << "\n";
  std::cout << "sizeof(combined): " << sizeof(combined) << "\n";
  
  // you can instantiate and then call composed function template
  std::cout << concat(f, g, h())(3, 4) << '\n'; // f(g(h(3, 4)))
}

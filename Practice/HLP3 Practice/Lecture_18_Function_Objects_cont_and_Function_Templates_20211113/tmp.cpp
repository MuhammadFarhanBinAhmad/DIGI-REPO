// CSD2125: 11/11
// We showcase the use of constexpr specifier, static_assert,
// and function templates to implement 2 functions that
// calculate M^N at compile time.
// The third method uses class template non-type parameters
// in conjunction with static data members to evaluate M^N
// at compile time.
#include <iostream>

// using plain-old-function with constexpr specifier to ensure
// the function is evaluated at compile time
constexpr int power(int m, int n) {
  int r{1};
  for (int k{1}; k <= n; ++k) {
    r *= m;
  }
  return r;
}

// using class template arguments like this: Power<2,10>::value
template <int M, int N>
struct Power {
  static int const value = M * Power<M, N-1>::value;
};

template <int M>
struct Power<M, 0> {
  static int const value = 1;
};

// using template arguments and function arguments: Power2<10>(2)
template <int M>
constexpr int Power2(int N) {
  return N * Power2<M-1>(N);
}

template <>
constexpr int Power2<1>(int N) {
  return N;
}

template <>
constexpr int Power2<0>(int M) {
  return 1;
}

int main() {
  constexpr int two_ten = power(2, 10);
  static_assert(two_ten == 1024);
  std::cout << two_ten << "\n";
  static_assert(Power<2, 10>::value == 1024);
  std::cout << Power<2, 10>::value << "\n";
  static_assert(Power2<10>(2) == 1024);
  std::cout << Power2<10>(2) << "\n";
}

// CSD2125 - 11/25
// This source file provides the motivation for type traits and
// shows how they can be used at compile-time.
// We have a function template byte_swap that should only be
// invoked with integral types that are not byte-sized.
// How do we ensure this type cannot be invoked on other types?
// The idea goes like this:
// 1) You define a class template, usually named with the type trait you're
// after (is_pointer, is_integer, is_void, ...). We choose is_swapable.
// 2) The class template must define a static const bool named value
// which defaults to a sensible state. In our case, the sensible state is false.
// 3) You make specializations of the class template representing the trait you
// want to expose, and have those set their bool value to a sensible state.
// In our case, we define class specializations with template parameter set to
// non-byte sized integral types with value set to true.
// 4) You then write code using the type trait by querying its value for a
// some template argument T: is_swapable<T>::value
// One last thing:
// The standard library provides a variety of type traits in <type_traits>.
// In the real world, rather than providing the definition of class template
// is_swapable and the different specializations, you would instead use the
// std::is_integral type trait like this:
//
// template <typename T> struct is_swapable {
//   static bool const value = std::is_integral<T>::value && sizeof(T) >= 2;
// };
#include <iostream>
#include <cassert>

template <typename T>
struct is_swapable {
  static bool const value = false;
};

template <>
struct is_swapable<unsigned short> {
  static bool const value = true;
};

template <>
struct is_swapable<short> {
  static bool const value = true;
};

template <>
struct is_swapable<unsigned int> {
  static bool const value = true;
};

template <>
struct is_swapable<int> {
  static bool const value = true;
};

template <>
struct is_swapable<unsigned long> {
  static bool const value = true;
};

template <>
struct is_swapable<long> {
  static bool const value = true;
};

template <>
struct is_swapable<unsigned long long> {
  static bool const value = true;
};

template <>
struct is_swapable<long long> {
  static bool const value = true;
};

#if 0
// specialization of template
template <>
double byte_swap(double value) {
  assert(false && "byte_swap requires integers");
  return value;
}

template <>
float byte_swap(float value) {
  assert(false && "byte_swap requires integers");
  return value;
}

template <>
long double byte_swap(long double value) {
  assert(false && "byte_swap requires integers");
  return value;
}
#endif

template <typename T>
T byte_swap(T value) {
  static_assert(is_swapable<T>::value && sizeof(T) > 1, "Cannot swap this type");
  uint8_t *bytes = reinterpret_cast<uint8_t*>(&value);
  for (size_t i{0}; i < sizeof(T); i+=2) {
    // switch value on left with value on right
    uint8_t v = bytes[i];
    bytes[i] = bytes[i+1];
    bytes[i+1] = v;
  }
  return value;
}

int main() {
  uint32_t orig = 0x11223344;
  std::cout << std::hex << std::showbase << orig << " | " << byte_swap(orig) << "\n";
  byte_swap(10L);
  // this will cause compile-time error
  byte_swap(10.1L);
}
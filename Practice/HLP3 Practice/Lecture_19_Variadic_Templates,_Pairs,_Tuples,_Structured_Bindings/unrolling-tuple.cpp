// CSD2125 11/06
// Template programming  to implement useful behavior for tuples.
#include <iostream>
#include <tuple>
#include <functional>

/*
Since tuples contain values of heterogeneous types, we cannot iterate
over tuples like this:

  auto t = std::tuple(1, 2.2, std::string{"tic-tac-toe"});
  for (auto const& v : t) {
    std::cout << v << " ";
  }

However, we can access every index of the tuple like this:

  auto t = std::tuple(1, 2.2, std::string{"tic-tac-toe"});
  std::cout << std::get<0>(t) << " ";
  std::cout << std::get<1>(t) << " ";
  std::cout << std::get<2>(t) << " ";

To iterate every index of the tuple, we need the number of types/values
contained in the tuple. Then, since the tuple contains different types,
we need to write a template metafunction that generates a new function
for every type in the tuple.
*/

// We start with a function that calls a callable f for a tuple
// value at a specific index:
template <size_t Index, typename Tuple, typename Func> 
void tuple_at(Tuple const& t, Func f) {
  // we've no idea of the type of value at Index ...
  auto const& v = std::get<Index>(t);
  // use std::invoke to call the callable f with value at index Index as argument
  std::invoke(f, v);
}

/*
We can now use tuple_at like this:

  auto t = std::tuple{1, 2.2, std::string{"tic-tac-toe"}};
  auto f = [](const auto& v) { std::cout << v << " "; };
  tuple_at<0>(t, f);
  tuple_at<1>(t, f);
  tuple_at<2>(t, f);

To iterate over the tuple elements, we need the number of values in the
tuple as a compile-time constant. Fortunately, this value can be obtained
by type trait std::tuple_size_v<Tuple> (or std::tuple_size(Tuple)::value).
Using if constexpr, we can unfold the iteration by creating a similar
function, which takes different actions, depending on the index:
a) If the index is equal to tuple size, it generates an empty function.
b) Otherwise, it executes the lambda at the passed index and generates a
new function with 1 added to the index
*/
template <typename Tuple, typename Func, size_t Index = 0>
void tuple_for_each(Tuple const& t, Func const& f) {
  constexpr auto n = std::tuple_size<Tuple>::value;
  if constexpr(Index < n) {
    tuple_at<Index>(t, f);
    tuple_for_each<Tuple, Func, Index+1>(t, f);
  }
}

// Implementation of std::any_of for std::tuple
template <typename Tuple, typename Func, size_t Index = 0> 
auto tuple_any_of(Tuple const& t, Func const& f) -> bool {
  // how many values in tuple? 
  constexpr auto n = std::tuple_size<Tuple>::value; 
  if constexpr(Index < n) { 
    bool success = std::invoke(f, std::get<Index>(t)); 
    if (success) {
      return true;
    }
    return tuple_any_of<Tuple, Func, Index+1>(t, f); 
  } else { 
    return false; 
  } 
}

int main() {
  auto t = std::tuple{1, true, std::string{"Jedi"}};
  tuple_for_each(t, [](const auto& v) { std::cout << v << " "; });
  std::cout << "\n";

  auto t2 = std::tuple{1, 1.2, 10, 10};
  std::cout << std::boolalpha << tuple_any_of(t2, [](auto const& v) { return v==0; }) << "\n";
}

// CSD2125 11/16
// Fold expressions allow us to compute the result of using a binary
// operator over ALL arguments of a parameter pack.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename... Types>
auto fold_sum_left(Types... params) {
  // parentheses required after return keyword
  return (... + params); // ((params1 + params2) + params3)
  // to deal with empty parameter packs
  //return (0 + ... + params);
}

template <typename... Types>
auto fold_sum_rght(Types... params) {
  return (params + ...); // (params1 + (params2 + params3))
  // to deal with empty parameter packs
  //return (params + ... + 0); // (params1 + (params2 + params3))
}

// Function that tells the occurrences in some range of
// the values we provide as variadic parameters
template <typename Range, typename ... Types>
auto matches(Range const& r, Types... params) {
  return (std::count(std::begin(r), std::end(r), params) + ...);
}

int main() {
  int val = 12;
  std::cout << fold_sum_left(47, 11, val, -1) << "\n";
  std::cout << fold_sum_left(std::string{"tic"}, "-", "tac", "-", "toe") << "\n";
  std::cout << fold_sum_rght("tic", "-", "tac", "-", std::string{"toe"}) << "\n";
  std::cout << fold_sum_left(1) << "\n";

  // matches ranges against individual items
#if 1
  std::vector<int> vi{1,2,3,4,5,6};
  std::cout << matches(vi,     2,6) << "\n"; // prints 2
  std::cout << matches(vi,     100) << "\n"; // prints 0
  std::cout << matches(std::initializer_list<std::string>{"tic", "tac", "toe"}, std::string{"tic"}, std::string{"toe"});
#endif
}
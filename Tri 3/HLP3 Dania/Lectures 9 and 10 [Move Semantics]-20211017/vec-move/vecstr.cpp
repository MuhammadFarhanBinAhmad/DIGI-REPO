/*
CSD2125
10/05
Driver to test behavior of std::vector<Vec<Str>> when Vec and Str
do and don't implement move semantics.

Without move semantics for Vec<> and Str:
g++ -std=c++17 vecstr.cpp str.cpp -o vecstr-nomove.out

You'll notice that without move semantics for Vec<> and Str classes:
20'000 default Str ctors are invoked and 20'000 copy ctors.
The 20'000 copy ctors allocate memory and copy all together 1.66 MB of information.

With move semantics for Vec<>:
g++ -std=c++17 vecstr.cpp str.cpp -D=VEC_MOVE vecstr-move.out

You'll notice that with move semantics for Vec<>:
10'000 default Str ctors are invoked and 10'000 copy ctors during the initial creation
of each Str object. These 10'000 copy ctors cannot be avoided!!!
*/
#include "vec.h"
#include "str.h"
#include <string>

Vec<Str> build_vecstr(size_t sz) {
  Vec<Str> result{sz};
  for (size_t i{0}; i < sz; ++i) {
    result[i] = "You should learn from your competitor and innovate, but never copy. Copy and you die.";
  }
  return result;
}

int main() {
  // create a vector container with 10 elements with each element of type Vec<Str>
  // that is, each element of the vector is a dynamic array of Str elements ...
  constexpr size_t vec_cnt{10};
  // create a Vec<Str> with 1'000 Str elements ...
  constexpr size_t str_per_vec{1'000};

  // create and put aside (uninitialized) memory for 10 Vec<Str> elements in a vector
  std::vector<Vec<Str>> vec_of_vecstrs;
  vec_of_vecstrs.reserve(vec_cnt);
  // for each Vec<Str> element, create a dynamic array with 1'000 Str elements with
  // each Str element encapsulating a C-string with 85 characters ...
  // all of this means that there will be 10'000 Str elements with each Str element
  // encapsulating 85 characters ...
  for (size_t i{}; i < vec_cnt; ++i) {
    vec_of_vecstrs.push_back(build_vecstr(str_per_vec));
  }

  // there are 10'000 Str elements with each Str element encapsulating 85 characters ...
  // how many ctors, dtors, and memory allocations/deallocation were invoked?
  std::cout << "str copies and moves: <" << Str::CopyCount() << ", " << Str::MoveCount() << ">\n";
  std::cout << "vec copies and moves: <" << Vec<Str>::CopyCount() << ", " << Vec<Str>::MoveCount() << ">\n";
}

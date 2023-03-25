// HLP2 04/01/2022
// numeric.cpp
// Illustrates three useful numeric algorithms declared in <numeric>:
// std::iota, std::accumulate, and std::inner_product
// Although std::accumulate is generally used for numeric processing,
// it can process other than numeric values. For example, std::accumulate
// can be used to process the sum of several std::strings.

// Further, the following sample code illustrates a variety of function
// objects, binary function templates, a function template to print
// values of containers, and use of std::generate algorithm.

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
// to use numeric algorithms, you've to include header <numeric>
#include <numeric>

namespace {

// function object to generate increasing values incrementally ...
template <typename T>
class IntGen {
public:
  IntGen(T v = T()) : val{v} {}
  T operator()() { T old_val{val}; ++val; return old_val; }
private:
  T val{};
};

// function object to add two values
template <typename T>
struct Add {
  T operator()(T const& x, T const& y) const { return x+y; }
};

// function template to read absolute value of two values
template <typename T>
T Myabs(T const& x, T const& y) {
  return std::abs(x-y);
}

// function template to return maximum of two values
template <typename T>
T const& Mymax(T const& x, T const& y) {
  return x < y ? y : x;
}

template <typename Cont>
void print(Cont const& coll, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << postfix;
}
} // end anonymous namespace

int main() {
// write sequential values starting from 10 to v1's elements
  std::vector<int> v1(5);
  std::generate(std::begin(v1), std::end(v1), IntGen<int>(10));
  print(v1, "v1: ");

// Numeric algorithm 1: iota
// void iota(ForwardIterator first, ForwardIterator last, T init_val)
// Assigns init_val, init_val+1, init_val+2, and so on to elements in [first, last)

// write sequential values starting from 10 to v1's elements
// std::iota has similar but simpler behavior as std::generate [shown above] ...
   std::iota(std::begin(v1), std::end(v1), 10);
   print(v1, "v1: ");

// Numeric algorithm 2a: accumulate
// accumulate(InputIterator first, InputIterator end, T init_val)
// Computes and returns the sum of init_val and all elements in range [first, end)
// Does the following for each element: init_val += elem
// Thus, for the values: a0 a1 a2 a3 ...
// we get: init_val + a0 + a1 + a2 + a3 + ...

// compute sum of elements of v1
  std::cout << "sum(v1)   : "
            << accumulate(std::begin(v1), std::end(v1), 0) << "\n";
// compute sum of elements of v1 less 10
  std::cout << "sum(v1)-10: "
            << accumulate(std::begin(v1), std::end(v1), -10) << "\n";

// Numeric algorithm 2b: accumulate [continued]
// T accumulate(InputIterator first, InputIterator end, T init_val, BinaryFunc op)
// Computes and returns the result of calling non-modifying function op for
// init_val and all elements in range [first, end)
// Does the following for each element: init_val = op(init_val, elem)
// Therefore, for values x0 x1 x2 ...
// the algorithm will compute init_val op x0 op x1 op x2 op ...

// compute product of elements of v1
  std::generate(std::begin(v1), std::end(v1), IntGen<int>(1));
  print(v1, "v1: ");
  std::cout << "product(v1): "
            << accumulate(std::begin(v1), std::end(v1), 1, std::multiplies<int>())
            << "\n";
  std::cout << "add(v1)    : "
            << accumulate(std::begin(v1), std::end(v1), 0, Add<int>{})
            << "\n";
  std::cout << "-add(v1)   : "
            << accumulate(std::begin(v1), std::end(v1), 0, std::minus<int>())
            << "\n";

// Numeric algorithm 3a: inner_product
// T inner_product(InputIterator first1, InputerIterator last1,
//                InputIterator first2, T init_val)
// Computes sum of products of two ranges + init_val
// Thus, for the values [in two ranges]:
// x0 x1 x2 ...
// y0 y1 y2 ...
// inner_product computes: init_val + (x0 * y0) + (x1 * y1) + (x2 * y2) + ...

// compute sum of products of ranges in v2 and v3 ...
  std::vector<int> v2{1, 2, 3, 4, 5};
  std::vector<int> v3{2, 6, 1, 5, 3};
// prints: 0 + (1*2) + (2*6) + (3*1) + (4*5) + (5*3)
  std::cout << std::inner_product(std::begin(v2), std::end(v2), std::begin(v3), 0) << "\n";

// Numeric algorithm 3b: inner_product [continued]
// T inner_product(InputIterator first1, InputIterator last1,
//                InputIterator first2, T init_val,
//                BinaryFunc op1, BinaryFunc op2)
// For the values [in two ranges]:
// x0 x1 x2 ...
// y0 y1 y2 ...
// inner_product computes: init_val op1 (x0 op2 y0) op1 (x1 op2 y1) op1 (x2 op2 y2) op1 ...
// prints: 0 + (1*2) + (2*6) + (3*1) + (4*5) + (5*3)
  std::cout << std::inner_product(std::begin(v2), std::end(v2),
                                  std::begin(v3), 0,
                                  std::plus<int>(), std::multiplies<int>()) << "\n";

// Some practical examples of inner_product:
// Suppose v2 and v3 represent individual player scores in team 1 and team 2, respectively
// We want to know the maximum difference in score between corresponding players ...
// We use inner_product to do this:
// 0 max abs(x0-y0) max abs(x1-y1) max abs(x2-y2) max ...
  std::cout << std::inner_product(std::begin(v2), std::end(v2),
                                  std::begin(v3), 0,
                                  Mymax<int>, Myabs<int>) << "\n";

// Suppose v4 represents player scores and you want to know how many
// adjacent players have similar score.
  std::vector<int> v4{1, 2, 2, 4, 5, 6, 6, 6, 7, 3};
// We use inner_product to do this:
// 0 + (x1==x0) + (x2==x1) + (x3==x2) + ...
  std::cout << std::inner_product(std::next(std::begin(v4)), std::end(v4),
                                  std::begin(v4), 0,
                                  std::plus<int>{}, std::equal_to<int>{}) << "\n";
}

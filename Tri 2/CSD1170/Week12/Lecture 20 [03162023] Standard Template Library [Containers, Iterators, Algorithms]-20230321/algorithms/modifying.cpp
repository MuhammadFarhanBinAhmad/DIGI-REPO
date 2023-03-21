// HLP2 04/01/2022
// modifying.cpp
// Here we look at algorithms that modify the elements of a range
// 1) Copying elements [covered here]
// 2) Transforming elements [covered here]
// 3) Assigning same value [covered here]
// 4) Assigning generated values [covered here]
// 5) Replacing values inside a sequence [not covered]
// 6) for_each algorithm [covered]

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>

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

template <typename Cont>
void print(Cont const& coll, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Cont::const_reference elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << postfix;
}

// fill values from first to last [both inclusive] into collection ...
template <typename Cont>
void insert_elements(Cont& coll, int first, int last) {
  for (; first <= last; ++first) {
    coll.push_back(first);
  }
}

// function object that defines a unary predicate for comparing
// each element in a sequence with a initial value ... 
template <typename T>
class GreaterThan {
public:
  GreaterThan(T const& v) : val{v} {}
  bool operator()(T const& v) const { return v > val; }
private:
  T val;
};

// function object that defines a unary function for multiplying
// a value with an initial value ...
template <typename T>
class MultiplyWith {
public:
  MultiplyWith(T const& v) : val{v} {}
  T operator()(T const& v) const { return v*val; }
private:
  T val;
};

// function object that replaces each element by its square ...
template <typename T>
struct Square {
  T operator()(T x) const { return x*x; }
};

} // end anonymous namespace

int main() {
// Copying elements 1a: copy
// OutputIterator
// copy(InputIterator first, InputIterator last, OutputIterator dest)
// Copy all elements of source range [first, last) into a destination
// range starting with dest.
// Returns the position after the last copied element in the destination range.
// Caller must ensure that destination range is big enough or that insert
// iterators are used.

// copy elements from one sequence into another sequence
  std::vector<std::string> v1{"today", "is", "a", "good", "day"};
  print(v1, "v1: ");
  std::list<std::string> l1;
  std::copy(std::begin(v1), std::end(v1), std::back_inserter(l1));
  print(l1, "l1: ");

// Copying elements 1b: copy_if
// OutputIterator
// copy_if(InputIterator first, InputIterator last, OutputIterator dest, UnaryPredicate op)
// Copy all elements of source range [first, last) into a destination range
// starting with dest if op(elem) is true.
// Returns the position after the last copied element in the destination range.
// Caller must ensure that destination range is big enough or that insert
// iterators are used.

// only copy elements with size larger than initial value  
  std::list<std::string> l2;
  std::copy_if(std::begin(v1), std::end(v1), std::back_inserter(l2), GreaterThan<std::string>{"abc"});
  print(l2, "l2: ");

// Transforming and combining elements
// std::transform provides two abilities:
// 1) The first form has four arguments. It transforms elements from a source to
// a destination range. Thus, this form copies and modifies elements in one step.
// 2) The second form has five arguments. It combines elements from two source
// sequences and writes the results to a destination range.

// Transforming elements algorithm 2a:
// OutputIterator
// transform(InputIterator first, InputIterator last, OutputIterator dest, UnaryFunc op)
// For each element elem in source range [first, last), writes op(elem) to the
// destination range starting with dest.
// Returns the position after the last transformed element in the destination range.
// first and dest can be identical.

// write values [1, 9] in v2 ...
  std::vector<int> v2;
  insert_elements(v2, 1, 9);
  print(v2, "v2: ");

// negate all elements in v2
  std::transform(std::begin(v2), std::end(v2), // source range
                 std::begin(v2),               // destination range
                 std::negate<int>{});          // operation
  print(v2, "v2: ");

// transform elements of v2 into v3 with ten times their value
  std::vector<int> v3;
  std::transform(std::begin(v2), std::end(v2), // source range
                 std::back_inserter(v3),       // destination range
                 MultiplyWith<int>{10});       // operation
  print(v3, "v3: ");

// print v3 negatively and in reverse order ...
  std::transform(v3.crbegin(), v3.crend(),                   // source range
                 std::ostream_iterator<int>(std::cout, " "), // destination range
                 std::negate<int>{});                        // operation
  std::cout << "\n";

// Transforming and combining elements algorithm 2b:
// OutputIterator
// transform(InputIterator1 first1, InputIterator1 last1,
//           InputIterator2 first2, OutputIterator dest, BinaryFunc op)
// Calls op(elem1, elem2) for all corresponding elements from the first source
// range [first1, last1) and the second range starting at first2 and writes
// each result in the destination range starting with dest.
// Returns the position after the last transformed element in the destination range.
// first and dest can be identical.

// write values [1, 9] in v4 ...
  std::vector<int> v4;
  insert_elements(v4, 1, 9);
  print(v4, "v4: ");

// square each element in v4
  std::transform(std::cbegin(v4), std::cend(v4), // source range 1
                std::cbegin(v4),                 // source range 2
                std::begin(v4),                  // destination range
                std::multiplies<int>{});         // binary operation
  print(v4, "v4: ");

// add each element traversed forward with each element traversed backward
// and insert result into l3
  std::list<int> l3;
  std::transform(std::cbegin(v4), std::cend(v4),
                 v4.crbegin(),
                 std::back_inserter(l3),
                 std::plus<int>{});
  print(l3, "l3: ");

// print difference of two corresponding elements in v4 and l3
  std::transform(std::cbegin(v4), std::cend(v4),             // source range 1
                 l3.crbegin(),                               // source range 2
                 std::ostream_iterator<int>(std::cout, " "), // destination range
                 std::minus<int>{});                         // binary operation
  std::cout << "\n";

// Assigning the same value 3: fill
// void fill(ForwardIterator first, ForwardIterator last, T const& value)
// Assigns value to each element in the range [first, last)
// Caller must ensure that destination range is big enough or that insert iterators are used.

// overwrite all values in v4 with 3 except first and last elements
  std::fill(++std::begin(v4), --std::end(v4), 3);
  print(v4, "v4: ");

// Assigning generate values 4: generate
// void generate(ForwardIterator first, ForwardIterator last, Func op)
// Assigns the values that are generated by a call of op() to each element in range [first, last)

// overwrite all values in v4 with sequential values starting from 10 ...
  std::generate(std::begin(v4), std::end(v4), IntGen<int>{10});
  print(v4, "v4: ");

// Modify each element in many different sets 6: for_each
// UnaryFirst for_each(InputIterator first, InputIterator last, UnaryFunc op)
// Calls op(elem) for each element in range [first, last). Here, op will modify
// the elements.
// This is the only algorithm that returns updated function object ...

// replace each value with its square ...
  v4.clear(); // remove all elements in container ...
  insert_elements(v4, 1, 9); // add values [1, 9] to v4 ...
  print(v4, "v4: ");
  std::transform(std::begin(v4), std::end(v4), std::begin(v4), Square<int>{});
  print(v4, "v4: ");
}

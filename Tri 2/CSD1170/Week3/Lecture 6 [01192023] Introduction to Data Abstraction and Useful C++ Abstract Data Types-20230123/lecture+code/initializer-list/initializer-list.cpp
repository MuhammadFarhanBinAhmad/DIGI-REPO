// HLP2: initializer-list.cpp
// 01/24/2022
// The following code illustrates the use of type std::initializer_list to
// write functions that take varying number of parameters of the same type.
// We replace "small" static arrays with functions that take an initializer_list<T>
// parameter where T indicates the "same" type of values in the initializer list. 

#include <initializer_list>
#include <iostream>

// accessing elements of initializer_list<double> using range-for loop ...
double average(std::initializer_list<double> values) {
  if (!values.size()) {
    return 0.;
  }
  double sum {};
  for (double x : values) {
    sum += x;
  }
  return sum/values.size();
}

// accessing elements of initializer_list<int> using global begin() and end()
// functions that return iterators [think of them for now as pointers] to
// first and one-past last element of initializer_list, respectively ...
double average(std::initializer_list<int> values) {
  if (!values.size()) { return 0; }
  int sum{};
#if 0
  for (int const *ptr = std::begin(values); ptr != std::end(values); ++ptr) {
    sum += *ptr;
  }
#else
  for (std::initializer_list<int>::const_iterator ptr = std::begin(values); ptr != std::end(values); ++ptr) {
    sum += *ptr;
  }
#endif
  return static_cast<double>(sum)/values.size();
}

int main() {
  std::cout << "Average: " << average({11.1}) << "\n";
  std::initializer_list<double> grades_dbl2{11.1, 22.2};
  std::cout << "Average: " << average(grades_dbl2) << "\n";
  std::cout << "Average: "  << average({11.1, 22.2, 33.3, 44.4, 55.5}) << "\n";

  std::cout << "Average: " << average({11}) << "\n";
  std::cout << "Average: " << average({11, 33}) << "\n";
  std::initializer_list<int> grades_int5{11,22,33,44,55};
  std::cout << "Average: " << average(grades_int5) << "\n";
}

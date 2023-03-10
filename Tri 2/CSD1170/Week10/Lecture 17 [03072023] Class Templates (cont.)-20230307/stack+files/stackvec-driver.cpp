#include "stackvec.hpp"      // for Stack<>
#include <iostream>           // for std::cout
#include <string>
#include <utility>            // for std::pair
#include <cctype>             // for std::toupper

int main() {
  // initialize int stack
  Stack<int> si{std::vector<int>{5, 10, 15, 20, 25}};
  Stack<int> si2; // test default ctor
  si2 = si; // test default copy assignment operator
  std::cout << "si2: " << si2 << '\n'; // print contents of stack:
  // manipulate int stack
  std::cout << "si2: ";
  while (!si2.empty()) {
    ++si2.top(); // increment value at top of stack
    std::cout << si2.top() << ' ';
    si2.pop(); // remove value at top of stack
  }
  std::cout << '\n';

  // initialize std::string stack (using specialized stack when #include "stack-spec-str.hpp" is uncommented)
  Stack<std::string> ss{std::vector<std::string>{"san diego", "san jose", "san pedro", "san mateo", "san rafael"}};
  Stack<std::string> ss2; // default ctor
  ss2 = ss; // test default copy assignment operator
  std::cout << "ss2: " << ss2 << "\n"; // print contents of stack:
  // manipulate string stack
  std::cout << "ss2: ";
  while (!ss2.empty()) {
    // change lowercase latin characters to uppercase
    std::string& str {ss2.top() };
    for (std::string::value_type& x : str) { x = std::toupper(x); }
    std::cout << ss2.top() << ' ';
    ss2.pop(); // remove value at top of stack
  }
  std::cout << '\n';

  // create type alias for std::pair<int, double>:
  using pid = std::pair<int, double>;
  // initialize pid stack
  Stack<pid> sp{std::vector<pid>{{1,1.1}, {2,2.2}, {3,3.3}, {4,4.4}, {5,5.5}}};
  Stack<pid> sp2; // test default ctor
  sp2 = sp; // test defaulted copy assignment operator
  
  /*
  You might have the impression that template arguments have to provide all
  operations necessary for all member functions of a class template. But this
  is not the case. Template arguments only have to provide all necessary
  operations that are needed instead of that could be needed.

  You can still use this class for elements that don't have operator<< defined
  such as std::pair<> as long as we don't write the statement:

  std::cout << "sp: " << sp << "\n";
  
  Only if you call operator<< for Stack<std::pair<>>, the code will produce an
  error, because it can't instantiate the call of operator<< for this
  specific type.

  To be able to print the elements of a Stack<std::pair<>>, you must add
  the following function template (anywhere before the definition of
  operator<<(std::ostream&, Stack<T> const&)):
  template <typename T1, typename T2>
  std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> const& rhs) {
    os << "{" << rhs.first << ", " << rhs.second << "} ";
    return os;
  }
  */
  //std::cout << "sp: " << sp << "\n";

  // manipulate std::pair stack
  std::cout << "sp: ";
  while (!sp.empty()) {
    pid& top_val = sp.top();
    top_val.first++; top_val.second++;
    std::cout << "{" << sp.top().first << ", " << sp.top().second << "}, ";
    sp.pop();
  }
  std::cout << '\n';
}

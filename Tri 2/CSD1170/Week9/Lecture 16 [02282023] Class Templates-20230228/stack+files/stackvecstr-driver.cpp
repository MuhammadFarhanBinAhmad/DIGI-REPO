#include "stackvec.hpp"    // for Stack<>
#include "stackvecstr.hpp" // for Stack<std::string>
#include <iostream>        // for std::cout
#include <string>          // for std::string
#include <utility>         // for std::pair
#include <cctype>          // for std::toupper

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

  // initialize std::string stack (using specialized stack when #include "stackvecstr.hpp" is uncommented)
  Stack<std::string> ss{std::deque<std::string>{"san diego", "san jose", "san pedro", "san mateo", "san rafael"}};
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

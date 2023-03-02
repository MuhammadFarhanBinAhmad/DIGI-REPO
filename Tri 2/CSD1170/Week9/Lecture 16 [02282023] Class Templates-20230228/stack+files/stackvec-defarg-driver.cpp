#include "stackvec-defarg.hpp" // for Stack<T, Cont>
#include <iostream>            // for std::cout
#include <string>              // std::string
#include <utility>             // for std::pair<T1,T2>
#include <cctype>              // for std::toupper
#include <deque>               // for std::deque<T>
#include <list>                // for std::list<T>

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

  // initialize std::string stack
  Stack<std::string, std::deque<std::string>> 
      ss{std::deque<std::string> {"san diego", "san jose", "san pedro", "san mateo", "san rafael"}};
  Stack<std::string, std::deque<std::string>> ss2; // test default ctor
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
  using PID = std::pair<int, double>;
  // another type alias for Stack<PID, std::list<PID>>
  using StackPID = Stack<PID, std::list<PID>>;
  // initialize PID stack
  StackPID sp{std::list<PID>{{1,1.1}, {2,2.2}, {3,3.3}, {4,4.4}, {5,5.5}}};
  StackPID sp2; // test default ctor
  sp2 = sp; // test defaulted copy assignment operator
  std::cout << "sp2: " << sp2 << "\n";

  // manipulate std::pair stack
  std::cout << "sp2: ";
  while (!sp2.empty()) {
    // increment values in element at top-of-stack ...
    PID& top_val = sp2.top();
    top_val.first++; top_val.second++;
    std::cout << "{" << sp2.top().first << ", " << sp2.top().second << "}, ";
    sp2.pop();
  }
  std::cout << '\n';
}

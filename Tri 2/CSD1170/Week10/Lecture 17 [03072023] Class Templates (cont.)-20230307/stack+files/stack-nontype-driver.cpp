#include "stack-nontype.hpp"
#include <string>
#include <vector>
#include <utility> // for std::pair

int main() {
  Stack<int, 5> si, si2; // test default ctor
  si.push(5); si.push(10); si.push(15); si.push(20); si.push(25);
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

  Stack<std::string, 6> ss, ss2; // test default ctor
  ss.push("san diego"); ss.push("san jose");   ss.push("san pedro");
  ss.push("san mateo"); ss.push("san rafael"); ss.push("san carlos");
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

  using PID = std::pair<int, double>; // create type alias for std::pair<int, double>
  Stack<PID, 6> sp, sp2; // test default ctors
  sp.push({1,1.1}); sp.push({2,2.2}); sp.push({3,3.3}); sp.push({4,4.4}); sp.push({5,5.5});
  sp2 = sp; // test defaulted copy assignment operator
  std::cout << "sp2: " << sp2 << "\n";

  // manipulate std::pair stack
  std::cout << "sp2: ";
  while (!sp2.empty()) {
    PID& top_val = sp2.top();
    ++top_val.first; --top_val.second;
    std::cout << top_val << ' '; //"{" << sp2.top().first << ", " << sp2.top().second << "}, ";
    sp2.pop();
  }
  std::cout << '\n';
}
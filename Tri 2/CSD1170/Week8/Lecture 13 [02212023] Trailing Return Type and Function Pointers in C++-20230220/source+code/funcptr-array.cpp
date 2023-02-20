// HLP2 05/26/2020
// funcptr-array.cpp:
// Illustrates the use of arrays of function pointers

#include <iostream>

int Add(int lhs, int rhs) { return lhs+rhs; }
int Sub(int lhs, int rhs) { return lhs-rhs; }
int Mul(int lhs, int rhs) { return lhs*rhs; }
int Div(int lhs, int rhs) { return lhs/rhs; }

enum class Op : int { ADD, SUB, MUL, DIV };

int main() {
  // Array of function pointers offers the possibility of selecting
  // a function using an index ...
  // An array of function pointers is known as a jump table [among many other names] ...
  int (*math_func[]) (int, int) { Add, Sub, Mul, Div };
    
  // evaluate multiplication expression ...
  std::cout << "2 * 3 = " <<  math_func[static_cast<int>(Op::MUL)](2, 3) << '\n';
  // evaluate more complex expression ...
  std::cout << "3.0 * (4.0 + 5.0) + 6.0 = "
            << math_func[static_cast<int>(Op::ADD)](
                 math_func[static_cast<int>(Op::MUL)](3, math_func[static_cast<int>(Op::ADD)](4, 5)), 6)
            << '\n';
}

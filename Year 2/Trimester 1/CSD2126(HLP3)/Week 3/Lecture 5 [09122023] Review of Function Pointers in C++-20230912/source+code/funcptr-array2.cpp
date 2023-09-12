// HLP2 05/26/2020
// funcptr-array2.cpp:
// Same as funcptr-array.cpp except that we use using aliases and
// C++11 trailing return type syntax for functions!!!

#include <iostream>

auto Add(int lhs, int rhs) -> int { return lhs+rhs; }
auto Sub(int lhs, int rhs) -> int { return lhs-rhs; }
auto Mul(int lhs, int rhs) -> int { return lhs*rhs; }
auto Div(int lhs, int rhs) -> int { return lhs/rhs; }

enum class Op : int { ADD, SUB, MUL, DIV };

auto enum_to_int(Op o) -> int {
  switch(o) {
    case Op::ADD: return 0;
    case Op::SUB: return 1;
    case Op::MUL: return 2;
    case Op::DIV: return 3;
  }
  return 0; // hack!!!
}

auto main() -> int {
  // Array of function pointers offers the possibility of selecting
  // a function using an index ...
  // An array of function pointers is known as a jump table [among many other names] ...
  //int (*math_func[]) (int, int) { Add, Sub, Mul, Div };
  using PTR_FUNC_INT2 = auto (*)(int,int) -> int;
  PTR_FUNC_INT2 math_func[] { Add, Sub, Mul, Div };
    
  // evaluate multiplication expression ...
  std::cout << "2 * 3 = " <<  math_func[enum_to_int(Op::MUL)](2, 3) << '\n';
  // evaluate more complex expression ...
  std::cout << "3.0 * (4.0 + 5.0) + 6.0 = "
            << math_func[enum_to_int(Op::ADD)](
                 math_func[enum_to_int(Op::MUL)](3, math_func[enum_to_int(Op::ADD)](4, 5)), 6)
            << '\n';
}

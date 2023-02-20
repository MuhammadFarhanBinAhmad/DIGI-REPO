// HLP2 05/26/2020
// fp-intro4.cpp:
// Same content as fp-intro2.cpp except all functions are declared and
// defined using C++11 trailing return type syntax and we use the
// C++11 using keyword to provide alias to complicated declarations!!!

#include <iostream>

// four functions to perform basic calculator-style functions
auto Add(int x, int y) -> int { return x+y; }
auto Sub(int x, int y) -> int { return x-y; }
auto Mul(int x, int y) -> int { return x*y; }
auto Div(int x, int y) -> int { return x/y; }

// function that evaluates an operator and invokes the function directly
// without resorting to function pointers ...
/*
When you want to call a function foo at a certain point - say label - in
your program, you use the function call operator and the explicit name of
the function [which is foo] to call function foo at the point label in
your source code. Then you compile your code and every time your program
comes up to the point label, function foo gets called.

What should you do if you have a variety of functions foo, boo, coo, ...
with the same signature and you want to decide at runtime which function
should be called? 

This problem can be solved using a switch statement where you call the
appropriate function in a specific branch of the switch statement.
As an example, the following function eval_switch takes an opcode
indicating the specific calculator function to call and the remaining
parameters specify the operands to the calculator function ...
*/
auto eval_switch(char opcode, int x, int y) -> int {
  switch (opcode) {
    case '+': return Add(x, y);
    case '-': return Sub(x, y);
    case '*': return Mul(x, y);
    case '/': return Div(x, y);
  }
  return 0;
}

/*
Function pointers provide an alternative way to solve the problem.
As an example, the function eval_switch_funcptr takes three parameters:
a pointer to the function to be executed and the remaining parameters
specify the operands to the to-be-called function:
*/
#if 0
int eval_switch_funcptr(auto (*FP)(int,int) -> int, int a, int b) {
  return FP(a, b);
}
#else
// The above function could also have been defined like this:
int eval_switch_funcptr(auto FP(int,int) -> int, int a, int b) {
  return FP(a, b);
}
#endif

/*
The function select is a different approach to eval_funcptr. This
function takes the operation code as a parameter and returns a
pointer to the calculator function that corresponds to the operation code.
However, the appropriate function pointer [that is returned by the function]
is selected using a switch statement ...
*/
//int (*select(char opcode))(int,int) {
auto select(char opcode) -> int (*)(int,int) {
  switch (opcode) {
    case '+': return Add;
    case '-': return Sub;
    case '*': return Mul;
    case '/': return Div;
    default: return nullptr;
  }
  return nullptr;
}

/*
Here is another variant. Function eval_noswitch receives three parameters:
the opcode specifying the calculator function to be invoked and the remaining
parameters specify the two operands to the calculator function ... 
Function select is called by eval_noswitch to obtain a function pointer to
the calculator function corresponding to the opcode ...
*/
auto eval_noswitch(char opcode, int x, int y) -> int {
  //int (*fp)(int, int) = select(opcode);
  using PTR_FUNC_INT2 = auto (*)(int,int) -> int;
  PTR_FUNC_INT2 fp {select(opcode)};
  return (*fp)(x, y);
}

auto main() -> int {
  std::cout << "Provide operator and operands: ";
  char opcode;
  int x, y;
  std::cin >> opcode >> x >> y;
  std::cout << x << " " << opcode << " " << y << " = "
            << eval_switch(opcode, x, y) << '\n';
  std::cout << x << " " << opcode << " " << y << " = "
            << eval_switch_funcptr(select(opcode), x, y) << '\n';
  std::cout << x << " " << opcode << " " << y << " = "
            << eval_noswitch(opcode, x, y) << '\n';

  // using eval_switch
  std::cout << "Testing eval_switch:\n";
  std::cout << "6  + 5 = " << eval_switch('+', 6, 5)  << '\n';
  std::cout << "6  - 5 = " << eval_switch('-', 6, 5)  << '\n';
  std::cout << "5  * 6 = " << eval_switch('*', 5, 6)  << '\n';
  std::cout << "10 / 2 = " << eval_switch('/', 10, 2) << '\n';

  // using eval_switch_funcptr
  std::cout << "Testing eval_switch_funcptr:\n";
  std::cout << "6  + 5 = " << eval_switch_funcptr(Add, 6,  5)  << '\n';
  std::cout << "6  - 5 = " << eval_switch_funcptr(Sub, 6,  5)  << '\n';
  std::cout << "5  * 6 = " << eval_switch_funcptr(Mul, 5,  6)  << '\n';
  std::cout << "10 / 2 = " << eval_switch_funcptr(Div, 10, 2)  << '\n';

  // using eval_noswitch
  std::cout << "Testing eval_noswitch:\n";
  std::cout << "6  + 5 = " << eval_noswitch('+', 6, 5)  << '\n';
  std::cout << "6  - 5 = " << eval_noswitch('-', 6, 5)  << '\n';
  std::cout << "5  * 6 = " << eval_noswitch('*', 5, 6)  << '\n';
  std::cout << "10 / 2 = " << eval_noswitch('/', 10, 2) << '\n';
}

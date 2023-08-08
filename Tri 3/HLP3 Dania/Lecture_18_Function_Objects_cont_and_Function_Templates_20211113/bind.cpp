// CSD2125: 11/09
// Source file showing purpose of std::bind, how to use std::bind, and
// also contains uses of standard function objects declared in <functional>.
//
// std::bind is a function adapter whose purpose is partial function application.
// It allows you to:
// a) adapt and compose new function objects out of existing or predefined
// function objects
// b) global objects
// c) call member functions for objects, pointers to objects, and smart
// pointers to objects (see bind2.cpp).
//
// In general, std::bind binds parameters for callables (function, member function,
// function object, lambda) to specific or passed arguments. Specific arguments
// you simply name. For passed arguments, you can use predefined placeholders _1, _2, ...
// defined in namespace std::placeholders.

#include <iostream>
#include <functional>

int main() {
  // plus10 represents a function object, which internally calls std::plus<> (operator +)
  // with a placeholder _1 as first parameter/operand and 10 as second parameter/operand.
  // _1 represents 1st argument passed to the expression as a whole. Thus, for any
  // argument passed to this expression, this function object yields value of that
  // argument +10
  auto plus10 = std::bind(std::plus<int>(), std::placeholders::_1, 10);
  std::cout << "+10: " << plus10(7) << "\n";
  
  // define a function object that takes one argument arg1 and passes it to
  // function object plus<int> with a second argument 10. 
  // the result (arg1+10) is now the first argument for multiplies<int>
  // with 2 as the second argument.
  // the result of the new function object is:  (arg1 + 10) * 2
  auto plus10times2 = std::bind(std::multiplies<int>(),
                                 std::bind(std::plus<int>(), std::placeholders::_1, 10),
                                 2);
  std::cout << "+10 *2: " << plus10times2(7) << "\n";
  
  // we can raise a value to power of 3 by combining two std::multiplies<>
  // objects with three placeholders for the argument passed:
  auto pow3 = std::bind(std::multiplies<int>(), // (param1 * param1) * param1
                        std::bind(std::multiplies<int>(),
                                  std::placeholders::_1, std::placeholders::_1),
                                  std::placeholders::_1);
  std::cout << "x*x*x: " << pow3(7) << "\n";
  
  // here, we define a function object where the arguments for a division are swapped:
  // so, instead of dividing 49 (argument 1) by 7 (argument 2), function object
  // inv_div will divide 7 (argument 2) by 49 (argument 1)
  auto inv_div = std::bind(std::divides<double>(),
                           std::placeholders::_2, std::placeholders::_1);
  std::cout << "inv_div: " << inv_div(49, 7) << "\n";

  // 1. Turn any argument bound to a variable into a capture variable
  // 2. Turn all placeholders into lambda args
  // 3. Specify all the arguments bound to a specific value directly in the lambda body
  //auto plus10times2 = std::bind(std::multiplies<int>(),
  //                               std::bind(std::plus<int>(), std::placeholders::_1, 10),
  //                               2);
  //std::cout << "+10 *2: " << plus10times2(7) << "\n";
  auto plus10times2_lambda = [](int x) { return (x+10) * 2; };
  std::cout << plus10times2_lambda(7) << "\n";

}

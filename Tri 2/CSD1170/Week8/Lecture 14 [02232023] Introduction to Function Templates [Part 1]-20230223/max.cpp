// HLP2: max.cpp
// 08/12/2021
// This source file provides a first look at function templates.
// Here, we declare and define a function template Max and explain
// the basic terminology you should be conversant with [keywords
// template and typename, function arguments and function parameters,
// template type argument, template type parameter, function template
// instantiation].
// We use the previously defined template Max to compare two ints,
// two doubles, and two std::strings.
// Using cppinsights.io and bash command nm, grep, and c++filt we're
// able to determine that the compiler is instantiating three function
// overloads:
// int Max(int, int);
// double Max(double, double);
// std::string Max(std::string, std::string)

#include <iostream>
#include <string>

// This is the definition of function template Max that returns the
// maximum of two values.
// The template definition specifies a family of functions that return the
// maximum of two values, which are passed as function parameter lhs and rhs.
// The types of function parameters lhs and rhs is left open as template type parameter T.
// As seen in the following function template definition, type parameters
// must be announced with syntax: template <typename T>
// If there are more than one template type parameters, they must be announced with
// the syntax: template <comma-separated-list-of-parameters>
// The keyword template announces a function template.
// The keyword typename introduces a template typename parameter [we can also
// have non-type parameters which will be introduced in another example].
// Here the type parameter is T. You can use any identifier as the type parameter,
// but using T is the convention.
// The type parameter represents an arbitrary type that is determined by the caller
// when the caller calls the function. You can use any type [built-in or 
// user-defined type] as long as it provides the operations used by the template.
// In the case of function template Max, the arbitrary type has to support opeator >
// because function parameters lhs and rhs are compared using this operator.
// The second operation that must be supported by the arbitrary type is copy
// construction. 
template <typename T>
T Max(T lhs, T rhs) {
  return lhs > rhs ? lhs : rhs;
}

int main() {
// Templates are not compiled into single entities that can handle any type.
// Instead, different entities are generated from the template for each type
// for which the template is used.
// In the following code, Max is called 3 times: once for two ints once for
// two doubles, and once for two std::strings.
// Here, Max is called for two ints. The call Max(i1, i2) will evaluate both
// the function arguments to be of type int. Thus, the compiler will look
// for the declaration of function Max that takes two int parameters. It will
// not find such a function. Instead, the function template declaration for
// Max is found with a single template parameter T and function parameters
// lhs and rhs that both have type T. The compiler will compare the types of
// the function arguments [int] with function parameters [T] to deduce that
// the template argument is type int. This process is known as template
// argument deduction.
// Recall from HLP1 that during function call evaluation: "parameters 
// [are variables] that are initialized with arguments [that are expressions]."
// With function templates, we have template parameter T [and function parameters
// lhs and rhs having type T] that will be initialized with the template argument
// type that was deduced by the compiler. The compiler will then generate the
// following function overload:
// int Max(int lhs, int rhs) {
//   return lhs > rhs ? lhs : rhs;
// }
// The compiler will replace expression Max(i1, i2) with a corresponding
// expression involving a call to the Max function that it just generated.
// Any subsequent calls to Max where both function arguments are of type int
// will also be replaced by a call to the instantiated Max function [the one 
// where both parameters are of type int].
// The process of replacing template parameters by concrete types is called
// template instantiation. This process results in an instance of the template.
// Note that the mere use of a function template can trigger such an instantiation
// process. There is no need for the programmer to explicitly request the
// instantiation.
  int i1{21}, i2{42};
  std::cout << Max(i1, i2) << '\n';

// Similarly, this call of Max(d1, d2) [where both function arguments evaluate
// to type double] will result in the instantiation of another function overload
// Max [where both function parameters have type double]. From the perspective
// of main's author, it is as though the function overload Max was individually
// declared and defined like this:
// double Max(double lhs, double rhs) {
//   return lhs > rhs ? lhs : rhs;
// }
  double d1{3.14}, d2{2.13};
  std::cout << Max(d1, d2) << '\n';

// Similarly, this call of Max(s1, s2) [where both function arguments evaluate
// type std::string] will result in the instantiation of a third function
// overload Max [where both function parameters have type std::string].
// From the perspective of main's author, it is as though the function
// overload Max was individually declared and defined like this:
// std::string Max(std::string lhs, std::string rhs) {
//   return lhs > rhs ? lhs : rhs;
// }
  std::string s1{"enjoy"}, s2{"enjoyment"};
  std::cout << Max(s1, s2) << '\n';

// Copy the code into the left frame of cppinsights.io, choose C++17
// as the compatible compiler, and press the [arrow] Run button to
// see the instantiations.
// Or, compile and link the code in this file and then run the following
// command in your Linux terminal to see the mangled names of the function
// overloads instantiated by the compiler:
// $ nm a.out | grep Max
// This will generate the following output in your terminal:
// _Z3MaxINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_S6_S6_
// _Z3MaxIdET_S0_S0_
// _Z3MaxIiET_S0_S0_
// If you want to see the unmangled names of the function overloads
// instantiated by the compiler, run this command(s):
// $ nm a.out | grep Max | c++filt
// to see the 3 unmangled function templates [specified with their 
// template argument types]:
// std::string Max<std::string>(std::string lhs, std::string rhs); [simplified form]
// double Max<double>(double lhs, double rhs);
// int Max<int>(int lhs, int rhs);
}

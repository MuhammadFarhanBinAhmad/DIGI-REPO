/*
CSD2125/CS225 05/24
signal3.cpp: Simplifying C++ complex declarations in signal2.cpp involving function 
pointers by using the trailing return syntax for functions and via alias declarations ...
Note that the trailing return syntax is available since C++11 ...
Note that typedef can be used and is compatible with all C++ standard, while
type aliases through keyword using is available since C++11 ...
*/
#include <iostream>

// signal_handler1 takes an int parameter and returns nothing ...
auto signal_handler1(int param) -> void {
//void signal_handler1(int param) {
  std::cout << "signal_handler:  " << param << "\n";
}

// signal_handler2 takes an int parameter and returns nothing ...
auto signal_handler2(int param) -> void {
//void signal_handler2(int param) {
  std::cout << "signal_handler2: " << param << "\n";
}

// signal0 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns nothing ...
using PTR_SIGHANDLER = void (*)(int);
auto signal0(int signum, PTR_SIGHANDLER ptr_sighandler) -> void {
//typedef void (*PTR_SIGHANDLER)(int);
//void signal0(int signum, PTR_SIGHANDLER ptr_sighandler) {
  ptr_sighandler(signum);
}

// signal1 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer
// to function signal_handler1 or signal_handler2 ...
auto signal1(int signum, PTR_SIGHANDLER ptr_sighandler) -> PTR_SIGHANDLER {
//PTR_SIGHANDLER signal1(int signum, PTR_SIGHANDLER ptr_sighandler) {
//void (*signal1(int signum, void (*ptr_sighandler)(int)))(int) {
  ptr_sighandler(signum);
  return signal_handler2;
}

// signal2 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer to
// function signal0 [which is a function that takes an int parameter and returns
// a pointer to function signal_handler1 or signal_handler2] ...
using PTR_SIGNAL0 = void (*)(int, PTR_SIGHANDLER);
auto signal2(int signum, PTR_SIGHANDLER ptr_sighandler) -> PTR_SIGNAL0 {
//typedef void (*PTR_SIGNAL0)(int, PTR_SIGHANDLER);
//PTR_SIGNAL0 signal2(int signum, PTR_SIGHANDLER ptr_sighandler) {
//void (*signal2(int signum, void (*ptr_sighandler)(int)))(int, void (*)(int)) {
  ptr_sighandler(signum);
  return signal0;
}

auto main() -> int {
  PTR_SIGHANDLER ptr_func = signal1(1, signal_handler1);
  //void (*ptr_func)(int) = signal1(1, signal_handler1);
  ptr_func(2);

  PTR_SIGNAL0 ptr_func2 = signal2(2, signal_handler2);
  //void (*ptr_func2)(int, void (*)(int)) = signal2(2, signal_handler2);
  ptr_func2(3, signal_handler1);
}

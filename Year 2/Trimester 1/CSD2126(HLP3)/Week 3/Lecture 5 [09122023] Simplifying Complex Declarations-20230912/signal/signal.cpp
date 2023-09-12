/*
CSD2125/CS225 05/24
signal.cpp: C++ Complex declarations involving function pointers ...
The code in this file is compatible with all C++ standards since C++98 ...
*/
#include <cstdio>

// signal_handler1 takes an int parameter and returns nothing ...
void signal_handler1(int param) {
  std::printf("signal_handler:  %d\n", param);
}

// signal_handler2 takes an int parameter and returns nothing ...
void signal_handler2(int param) {
  std::printf("signal_handler:  %d\n", param);
}

// signal0 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns nothing ...
void signal0(int signum, void (*ptr_sighandler)(int)) {
  ptr_sighandler(signum);
}

// signal1 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer
// to function signal_handler1 or signal_handler2 ...
void (*signal1(int signum, void (*ptr_sighandler)(int)))(int) {
  ptr_sighandler(signum);
  return signal_handler2;
}

// signal2 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer to
// function signal0 [which is a function that takes an int parameter and returns
// a pointer to function signal_handler1 or signal_handler2] ...
void (*signal2(int signum, void (*ptr_sighandler)(int)))(int, void (*)(int)) {
  ptr_sighandler(signum);
  return signal0;
}

int main() {
  void (*ptr_func)(int) = signal1(1, signal_handler1);
  ptr_func(2);

  void (*ptr_func2)(int, void (*)(int)) = signal2(2, signal_handler2);
  ptr_func2(3, signal_handler1);
}

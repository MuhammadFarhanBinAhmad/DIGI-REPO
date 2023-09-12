/*
CSD2125/CS225 05/24
signal2.cpp: Simplifying complex declarations involving function pointers in signal.cpp
with the typedef storage specifier keyword that allows us to declare new names
for existing types ...
The typedef keyword works in all versions of C and C++ standards ...
*/
#include <cstdio>

// signal_handler1 takes an int parameter and returns nothing ...
void signal_handler1(int param) {
  std::printf("signal_handler:  %d\n", param);
}

// signal_handler2 takes an int parameter and returns nothing ...
void signal_handler2(int param) {
  printf("signal_handler2: %d\n", param);
}

// signal0 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns nothing ...
typedef void (*PTR_SIGHANDLER)(int);
void signal0(int signum, PTR_SIGHANDLER ptr_sighandler) {
//void signal0(int signum, void (*ptr_sighandler)(int)) {
  ptr_sighandler(signum);
}

// signal1 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer
// to function signal_handler1 or signal_handler2 ...
PTR_SIGHANDLER signal1(int signum, PTR_SIGHANDLER ptr_sighandler) {
//void (*signal1(int signum, void (*ptr_sighandler)(int)))(int) {
  ptr_sighandler(signum);
  return signal_handler2;
}

// signal2 takes an int parameter and a pointer to function
// signal_handler1 or signal_handler2 and returns a pointer to
// function signal0 [which is a function that takes an int parameter and returns
// a pointer to function signal_handler1 or signal_handler2] ...
typedef void (*PTR_SIGNAL0)(int, PTR_SIGHANDLER);
PTR_SIGNAL0 signal2(int signum, PTR_SIGHANDLER ptr_sighandler) {
//void (*signal2(int signum, void (*ptr_sighandler)(int)))(int, void (*)(int)) {
  ptr_sighandler(signum);
  return signal0;
}

int main() {
  PTR_SIGHANDLER ptr_func = signal1(1, signal_handler1);
  //void (*ptr_func)(int) = signal1(1, signal_handler1);
  ptr_func(2);

  PTR_SIGNAL0 ptr_func2 = signal2(2, signal_handler2);
  //void (*ptr_func2)(int, void (*)(int)) = signal2(2, signal_handler2);
  ptr_func2(3, signal_handler1); 
}

#include <iostream>

// declarations of some static functions ...
void foo(int);
void boo(int);

// easy to declare complex declarations using typedef
using signum_t = void (*)(int);
signum_t signal_t(int, signum_t);
signum_t signal_t(int x, signum_t cb) {
  cb(x); // call the callback function
  return boo; // return pointer to global/static function boo
}

// this is harder to read because there is no synctatic
// sugercoating ...
// this function has the same "type" as signal_t
void (* mysignal(int x, void (*cb)(int)))(int) {
  cb(x); // call the callback function
  return foo; // return pointer to global/static function foo
}

// two tests functions that both take an int and return void ...
void foo(int x) {
  std::cout << "foo(" << x << ")\n";
}

void boo(int x) {
  std::cout << "boo(" << x << ")\n";
}

int main() {
  // call signal_t with foo as parameter
  signum_t ps = signal_t(1, foo);
  // call function whose pointer was returned by signal_t
  ps(2);

  // call mysignal with boo as parameter
  ps = mysignal(11, boo);
  // call function whose pointer was returned by mysignal ...
  ps(12);

  // to check signal_t and signal_t have same signature ...
  void (* (*ptr_sig)(int x, void (*cb)(int)))(int) = signal_t;
  // call signal_t thro' ptr_sig
  ps = ptr_sig(1, foo);
  ps(2);

  // now call mysignal through ptr_sig
  ptr_sig = mysignal;
  ps = ptr_sig(11, boo);
  ps(12);
}

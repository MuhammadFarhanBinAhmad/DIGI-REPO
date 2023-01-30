#include <iostream>
#include "wc.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "usage: lab1.out one-text-file two-text-file ...\n";
    return 0;
  }

  std::cout << argc << "\n";

  hlp2::wc(argc, argv);
}

// HLP2
// 01/12/2022
// This is a more robust version of the program in input-error01.cpp
// that can survive invalid integer input.

#include <iostream>

int main() {
  int i = -11;
  // as long as input stream cannot read an integer value,
  // continue prompting user to provide an integer value ...
  do {
    if (std::cin.fail()) {
      std::cin.clear(); // first clear stream's error state
      std::cin.ignore(1000, '\n'); // then have stream ignore either
                                   // 1000 characters in stream
                                   // or if character '\n' is extracted from stream
                                   // or if end-of-file condition is reached
      // 1000 is a magic number - what if there are more than 1000 characters
      // in the stream? The proper way is to ignore the maximum possible number
      // of characters that can be in a stream [requires inclusion of <limits>]
      //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Enter integer value: ";
    std::cin >> i;
  } while (!std::cin.good());
  // previous condition can be idiomatically written as:
  // } while (!std::cin);

  // ok: finally, we've valid integer data ...
  std::cout << "i==" << i << "\n";

  std::cout << "Enter fractional value: ";
  double d = 1.1;
  std::cin >> d;
  std::cout << "d==" << d << "\n"; 
}
// HLP2
// 01/12/2022
// This is a more robust version of the program in input-error03.cpp
// that can survive character strings longer than character array size.

#include <iostream>

int main() {
  std::cout << "Enter string [no more than 9 characters wide]: ";

  // Since array size is 10, the program should prevent std::cin
  // from reading more than 9 characters [plus null-terminating
  // character].
  // If user types "Supercalifragilistic", then only characters "Supercali"
  // should stored in array str while the remaining characters "fragilistic"
  // must be ignored ...
  char str[10];
  // good habit: leave things the way they were ...
  std::streamsize old_width = std::cin.width(sizeof(str)); // copy stream's current width
  std::cin >> str; // read maximum of nine characters ...
  std::cin.width(old_width); // reset stream with original width
  std::cin.ignore(1000, '\n'); // ignore any other characters in stream including '\n'

  std::cout << "Enter an integer value: ";
  int i;
  std::cin >> i;

  std::cout << "You entered: " << str << " | " << i << "\n";
}
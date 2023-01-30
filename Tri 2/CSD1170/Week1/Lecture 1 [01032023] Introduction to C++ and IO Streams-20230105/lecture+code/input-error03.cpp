// HLP2
// 01/12/2022
// This program illustrates a careless user that enters a 
// string with more characters than advised by the program.

#include <iostream>

int main() {
  std::cout << "Enter string [no more than 9 characters wide]: ";
  
  // Since array size is 10, the program will have undefined behavior
  // if more than 9 characters [plus null-terminating character] is
  // copied to array str ...
  char str[10];
  std::cin >> str; // hopefully, user won't type string with more than 9 characters ...

  std::cout << "Enter an integer value: ";
  int i;
  std::cin >> i;

  std::cout << "You entered: " << str << " | " << i << "\n";
}
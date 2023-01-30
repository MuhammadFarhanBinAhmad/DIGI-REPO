// HLP2: string-getline.cpp
// 01/24/2022
// The string input operator >> reads and discards any leading whitespace
// (spaces, newlines, tabs). It then reads characters until the next whitespace
// character is encountered. Sometimes we don't want to ignore the whitespace in
// our input. In such cases we can use the global getline function instead of
// operator >> - the use of this function is illustrated in this source file.

#include <string>
#include <iostream>

int main() {
  std::cout << "Enter your full name: ";
  std::string full_name; // default construction

  // the string input operator will discard any leading whitespace (spaces,
  // newlines, tabs). It then reads characters until the next whitespace
  // character is encountered.
  // sometimes we don't want to ignore the whitespace in our input. In such
  // cases, we can use the getline function instead of the string input
  // operator >>.
  // this function reads the given stream up to and including the first
  // newline and stores what it read - not including the newline - in its
  // string argument.
  getline(std::cin, full_name);
  std::cout << "Hello " << full_name << "!!!\n";
}

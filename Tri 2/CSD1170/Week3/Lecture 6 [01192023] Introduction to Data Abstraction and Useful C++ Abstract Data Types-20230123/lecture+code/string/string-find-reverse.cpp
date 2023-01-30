// HLP2: string-find-reverse.cpp
// 01/24/2022
// The following program extracts single words from standard input and prints
// the characters of each word in reverse order. The words are separated by
// the usual whitespace (newline, space, and tab) and by commas, periods, or
// semicolons.
// The program illustrates the find interface of strings.

#include <iostream>
#include <string>

int main() {
  std::cout << "Enter a sequence of words to be reversed: ";

  using str_size = std::string::size_type;
	
  // set of characters delimiting a word ...
  const std::string delims(" \t,.;");
  std::string line;
  while (std::getline(std::cin, line)) { // for every line read successfully
    // search for beginning of the first word
    str_size begIdx = line.find_first_not_of(delims);
    
    // while beginning of a word found
    while (begIdx != std::string::npos) {
      // search end of the actual word
      str_size endIdx = line.find_first_of(delims, begIdx);
      if (endIdx == std::string::npos) {
        // end of word is end of line
        endIdx = line.length();
      }
			
      // print characters in reverse order
      for (int i = endIdx-1; i >= static_cast<int>(begIdx); --i) {
        std::cout << line[i];
      }
      std::cout << ' ';
			
      // search beginning of the next word
      begIdx = line.find_first_not_of(delims, endIdx);
    }
    std::cout << "\nEnter a sequence of words to be reversed: ";
  }
}

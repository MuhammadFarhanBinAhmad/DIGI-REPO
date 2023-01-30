// HLP2
// 01/12/2022
// This program illustrates file I/O:
// the purpose is to read a sequence of unknown number of int values
// from an input text file and write only non-repeating adjacent
// values to an output file.
// compile and link: g++ -std=c++17 -pedantic -Wall -Wextra -Werror fileio.cpp
// usage: ./a.out input-file.txt unique-file.txt
// use accompanying text file numbers.txt or create your own.

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  // check if program is invoked with proper inputs ...
  if (argc < 3) {
    std::cout << "Usage: fileio.exe "
              "file-name-to-read-from-containing-ints "
              "new-file-name-containing-unique-ints\n";
    return 0;
  }

  // check if input file can be opened?
  std::fstream ifs(argv[1], std::ios_base::in);
  if (!ifs.is_open()) {
    std::cout << "Unable to open " << argv[1] << "\n";
    return 0;
  }

  // check if output file can be created?
  std::fstream ofs(argv[2], std::ios_base::out);
  if (!ofs.is_open()) {
    std::cout << "Unable to create " << argv[2] << "\n";
    return 0;
  }

  bool first_time = true;
  int previous_value, current_value;
  while (ifs >> current_value) {
    // when we read the first value, there is no previous value -
    // so we just write the value to output file stream ...
    if (first_time) {
      first_time = false;
      previous_value = current_value;
      ofs << current_value << ' ';
      continue;
    }

    // identify if previous_value is equivalent to current_value
    if (previous_value != current_value) {
      previous_value = current_value;
      ofs << current_value << ' ';
    }
  }
  ofs << "\n"; // write a newline in output file stream ...
  
  // close file streams
  ifs.close();
  ofs.close();
}
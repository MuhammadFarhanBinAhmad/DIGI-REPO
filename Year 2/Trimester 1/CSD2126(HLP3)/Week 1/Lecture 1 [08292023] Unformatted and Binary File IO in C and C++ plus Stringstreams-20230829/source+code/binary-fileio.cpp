// HLP3
// 08/16/2022
// This program illustrates binary file I/O:
// the purpose is to read a sequence of unknown number of int values
// from an input binary file and write only non-repeating adjacent
// values to an output binary file.
// compile and link: g++ -std=c++17 -pedantic -Wall -Wextra -Werror fileio.cpp
// usage: ./a.out input-file.bin unique-file.bin
// use accompanying bin file numbers.bin or create your own.

// When we move from character-oriented I/O to binary I/O, we give up
// our usual >> and << operators. These operators specifically turn
// values into character sequences using the default conventions [e.g., the
// string "asdf" turns into the characters a, s, d, f and the integer 123
// turns into the characters 1, 2, 3]. If we wanted that, we wouldn't need to
// say binary - the default would suffice. We use binary only if we [or someone
// else] thought that we somehow could do better than the default.
// We use binary to tell the stream not to try anything clever with the bytes!!!

#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  // check if program is invoked with proper inputs ...
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " "
              << "binary-file-name-to-read-from-containing-ints "
                 "new-binary-file-name-containing-unique-ints\n";
    return 0;
  }

  // check if input file can be opened?
  std::fstream ifs(argv[1], std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    std::cout << "Unable to open " << argv[1] << "\n";
    return 0;
  }

  // check if output file can be created?
  std::fstream ofs(argv[2], std::ios::out | std::ios::binary);
  if (!ofs.is_open()) {
    std::cout << "Unable to create " << argv[2] << "\n";
    return 0;
  }

  bool first_time = true;
  int previous_value, current_value;

  // The istream.read() takes an address [supplied here by &current_value] and
  // the number of bytes [characters] which we obtain by using sizeof(int).
  // The address should refer to the first byte of memory that will hold the
  // 4-byte value we will read from a file. For example, after reading an int 
  // with the decimal value 1234 from a binary file, current_value would
  // contain the following 4 bytes [in hex notation]: 0x00, 0x00, 0x04, 0xd2.
  while (ifs.read(reinterpret_cast<char*>(&current_value), sizeof(int))) {
    // when we read the first value, there is no previous value -
    // so we just write the value to output file stream ...
    if (first_time) {
      first_time = false;
      previous_value = current_value;
      ofs.write(reinterpret_cast<char*>(&current_value), sizeof(int));
      continue;
    }

    // identify if previous_value is equivalent to current_value
    if (previous_value != current_value) {
      previous_value = current_value;
      ofs.write(reinterpret_cast<char*>(&current_value), sizeof(int));
    }
  }
  
  // close file streams
  ifs.close();
  ofs.close();
}

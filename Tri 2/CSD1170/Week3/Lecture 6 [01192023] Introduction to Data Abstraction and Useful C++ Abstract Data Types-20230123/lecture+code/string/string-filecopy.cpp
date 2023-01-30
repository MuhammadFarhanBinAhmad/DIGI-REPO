// HLP2: string-filecopy.cpp
// 01/24/2022
// The fstream header defines three types to support file I/O:
// ifstream to read from a given file, ofstream to write to a given file, 
// and fstream which reads and writes a given file. These types inherit
// behaviors from the iostream types istream, ostream, and iostream and are
// specialized to manage the file associated with the stream. This means that
// we can use I/O operators (<< and >>) to read and write files, and we can
// use getline to read an ifstream.
// This source file puts strings and file I/O together to write a file copy
// program. You'll need a text file to test the program.

#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: ./a.out input-file-name copy-file-name\n";
    return 0;
  }

  /*
  The fstream header defines three types to support file I/O: ifstream to read
  from a given file, ofstream to write to a given file, and fstream which
  reads and writes a given file (not used in this example).
  These types inherit from the iostream types (ifstream from istream; ofstream
  from ostream; fstream from iostream). This means that ifstream and ofstream
  provide the same operations as those we've used on objects cin and cout,
  respectively. In particular, the types ifstream and ofstream add members to
  manage the file associated with the stream. All of this means that we can
  use IO operators (>> and <<) to read and write files, we can use getline to
  read an ifstream.
  */

  // associate file to read from with an input file stream ifs
  std::ifstream ifs {argv[1]};
  if (!ifs) {
    std::cout << "Unable to open input file " << argv[1] << "\n";
    return 0;
  }

  // associate file to write to with an output file stream ofs
  std::ofstream ofs {argv[2]};
  if (!ofs) {
    std::cout << "Unable to open output file " << argv[2] << "\n";
    return 0;
  }

  /*
  The getline function takes an input stream (note that an input file stream
  is also an input stream) and a string. This function reads the given stream
  up to and including the first newline and stores what it read - not including
  the newline - in its string argument. After getline sees a newline, even if
  it is the first character in the input, it stops reading and returns. If the
  first character in the input is a newline, then the resulting string is the
  empty string.
  Like the input operator, getline returns an istream (but remember that ifstream
  is-an istream too). As a result, we can use getline as a condition. Why?
  Because expression getline(ifs, line) evaluates to reference to ifstream.
  Therefore, getline(ifs, line) tests ifs. When we use an ifstream as a condition,
  the effect is to test the state of the stream. If the stream is valid - that is,
  if the stream hasn't encountered an error - then the test succeeds. An ifstream
  becomes invalid when it hits the end-of-file. An ifstream that is in an invalid
  state will cause the condition to yield false.
  */
  int line_ctr {0};
  std::string line;
  while (getline(ifs, line)) {
    // we just write to output file stream as though we're writing to
    // an ordinary output stream.
    // we've to add newline because getline discards newlines.
    ofs << line << "\n";
    ++line_ctr;
  }
  ifs.close();
  ofs.flush(); // request all characters in buffer to be written to file
  ofs.close();

  std::cout << line_ctr << " lines in file " << argv[1] << "\n";
}

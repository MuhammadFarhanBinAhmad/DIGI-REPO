// HLP3 225 05/14
// file-position.cpp - positioning in files using istream::seekg(), istream::tellg(),
// and ostream::seekp() and ostream::tellp()

// compile and link: g++ -std=c++17 -pedantic -Wall -Wextra -Werror file-position.cpp
// usage: ./a.out position.txt

// Please be careful: there is next to no run-time error checking when you use
// file positioning. In particular, it is undefined what happens if you try to
// seek [using seekg() or seekp()] beyond the end of a file, and operating
// systems read do differ in what happens then. 

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " binary-file-to-read\n";
    return 1;
  }

  std::fstream fs{argv[1]};

  // print contents of file ...
  std::cout << fs.rdbuf();
  // move reading position [g for "get"] to beginning of file ...
  fs.seekg(0);
  // print contents of file a second time ...
  std::cout << fs.rdbuf();

  // move reading position [g for "get"] to 5 from beginning of file
  fs.seekg(5, std::ios::beg);
  char ch;
  fs >> ch; // read and increment reading position
  std::cout << "character[5] is " << ch << '(' << static_cast<int>(ch) << ')' << "\n";
  std::cout << "current get position: " << fs.tellg() << "\n"; 

  // move writing position [p for "put"] to 1 from beginning of file
  fs.seekp(1);
  fs << 'y';

  // move reading position [g for "get"] to beginning of file ...
  fs.seekg(0);
  // print contents of file a third time ...
  std::cout << fs.rdbuf();

  fs.close();
}

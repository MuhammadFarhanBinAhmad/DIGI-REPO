// HLP3 05/14
// binfilew.cpp - write a binary file (C++ version)
//
// g++ doesn't like line 27 even though the logic in this program is correct.
// To avoid compiler errors, use the following to compile/link:
// g++ -std=c++17 -pedantic-errors -Wall -Wextra -Werror
//    -Wno-stringop-truncation binfilew.c -o binfilew.out

#include <iostream>
#include <fstream>
#include <cstring>
#include "file-struct.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " binary-file-to-create\n";
    return 1;
  }

  std::fstream out(argv[1], std::ios_base::binary | std::ios_base::out);
  if (!out) {
    std::cerr << "Unable to create file " << argv[1] << "\n";
    return 1;
  }

  char magic_number[2];
  std::strncpy(magic_number,MAGIC_NUMBER,2);
  out.write(magic_number,2);

  FileStruct fs {41, 182.f, "Barney Rubble"};
  out.write(reinterpret_cast<char*>(&fs),sizeof(fs));

  fs.age = 2;
  fs.weight = 45.3f;
  std::strcpy(fs.name,"Bam-bam Rubble");
  out.write(reinterpret_cast<char*>(&fs),sizeof(fs));
}

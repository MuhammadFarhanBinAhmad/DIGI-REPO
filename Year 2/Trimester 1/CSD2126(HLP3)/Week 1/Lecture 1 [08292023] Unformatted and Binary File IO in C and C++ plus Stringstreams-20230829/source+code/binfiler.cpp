// HLP3 225 05/14
// binfiler.cpp - read a binary file (C++ version)

#include <fstream>
#include <iostream>
#include <cstring>
#include "file-struct.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " sbinary-file-to-read\n";
    return 1;
  }
  
  std::ifstream in(argv[1], std::ios_base::binary|std::ios_base::in);
  if (!in) {
    std::cerr << "file not found\n";
    return 1;
  }

  char magic_number[2];
  in.read(magic_number,2);
  if (std::strncmp(magic_number,MAGIC_NUMBER,2) != 0) {
    std::cerr << "bad file\n";
    return 1;
  }

  // sanity check ...
  in.seekg(0, std::ios_base::end);
  int size = int(in.tellg());
  in.seekg(2, std::ios_base::beg);
  if ((size-2)%sizeof(FileStruct) != 0) {
    std::cerr << "bad or incomplete file\n";
    return 1;
  }

  while (in) {
    FileStruct fs;
    in.read(reinterpret_cast<char*>(&fs),sizeof(fs));
    if (in)
      std::cout << "Name: " << fs.name << std::endl
                << "  Age: " << fs.age << std::endl
                << "  Weight: " << fs.weight << std::endl;
  }
}

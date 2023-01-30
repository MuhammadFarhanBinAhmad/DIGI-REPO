/*
To build the program, type in your Linux shell:
make all
To test the program, type:
make test-all
*/
#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <vector>   // std::vector<std::string>
#include <iterator> // std::istream_iterator<std::string>
#include "q.h"      // check_distinct

int main(int argc, char *argv[]) {
  // sanity test to make sure program usage is correct
  if (argc < 3) {
    std::cout << "Usage: ./q.out input-text-file output-text-file\n";
    return 0;
  }

  // sanity test to make sure input file can be opened for reads
  std::ifstream ifs {argv[1]};
  if (!ifs) {
    std::cout << "Unable to open input file " << argv[1] << std::endl;
    return 0;
  }
  std::istream_iterator<int> is{ifs}; // is points to first int in file
  std::istream_iterator<int> eos; // eos now points to end-of-file
  std::vector<int> values(is, eos); // fill values with ints from file
  ifs.close(); // return file resource back to system ...
  std::ofstream ofs {argv[2]};
  if (!ofs) {
    std::cout << "Unable to open output file " << argv[2] << std::endl;
    return 0;
  }
  ofs << "Elements are " << (hlp2::check_distinct(values) ? "" : "not") 
            << " distinct.\n";
  ofs.close();
}

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "puncstream.hpp"

int main(int argc, char *argv[]) {
std::ifstream ifs{argv[1]};
hlp2::punc_stream ps{ifs};
ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~"); // note \“ means ”
ps.case_sensitive(false); // case-insensitive
std::map<std::string,size_t> histogram;
// insert words in file into histogram ...
for (std::vector<std::string> words; ps>>words; ) {
for (std::string const& word : words) { ++histogram[word]; }
}
// print frequency counter as shown in previous examples
}
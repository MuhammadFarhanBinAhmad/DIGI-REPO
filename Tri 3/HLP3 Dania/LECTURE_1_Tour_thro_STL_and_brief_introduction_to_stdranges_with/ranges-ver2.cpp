// imperative programming:
// functional decomposition: still procedural
// 09/07/2021
// since parameter argc is not used, don't use -Werror flag

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int count_lines(std::string const& file_name) {
  int line_count{};
  char ch{};
  std::ifstream ifs{file_name};
  
  while (ifs.get(ch)) {
    line_count = ('\n' == ch) ? line_count+1 : line_count;
  }
  return line_count;
}

std::vector<int> count_lines_in_file(std::vector<std::string> const& files) {
  std::vector<int> results;

  for (std::string const& fname : files) {
    results.push_back(count_lines(fname));
  }
  return results;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> file_names;
  int i{1};
  while (argv[i] != nullptr) {
    file_names.emplace_back(std::string(argv[i]));
    ++i;
  }

  std::vector<int> line_ctr = count_lines_in_file(file_names);
  int sum{};
  for (int val : line_ctr) {
    sum += val;
  }
  std::cout << "total number of lines: " << sum << "\n";
}
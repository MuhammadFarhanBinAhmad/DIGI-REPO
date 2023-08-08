// ranges1.cpp
// this is similar to programming quiz 1 except that files are
// read from standard input
// the following code is an example of imperative programming:
// imperative means we command the computer to do something by
// explicitly stating each step it needs to perform in order to
// calculate the result.
// 09/07/2021
// since parameter argc is not used, don't use -Werror flag

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> count_lines_in_file(std::vector<std::string> const& files) {
  std::vector<int> results;
  char ch{};

  for (std::string const& fname : files) {
    int line_count{};
    std::ifstream ifs{fname};
    while (ifs.get(ch)) {
      line_count = ('\n' == ch) ? line_count+1 : line_count;
    }
    results.push_back(line_count);
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
  std::cout << "sum: " << sum << "\n";
}

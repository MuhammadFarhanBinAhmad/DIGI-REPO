// The problem is that the previous code includes too much boilerplate
// code to be considered more readable than the original example.
// The function has only three important words:
//   transform - what the code does
//   files - input
//   count_lines - transformation function
// The rest is noise.
// The function could be more readable if you could write the
// important bits and skip everything else.
// 09/07/2021
// since parameter argc is not used, don't use -Werror flag
// must be compiled using g++-10 and -std=c++20

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <ranges>
#include <typeinfo>

int count_lines(std::string const& file_name) {
  std::ifstream ifs{file_name};
  return std::count(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), '\n');
}

int main(int argc, char *argv[]) {
  //std::vector<int> line_ctr = count_lines_in_file(std::vector<std::string>(argv+1, argv+argc));
  //int sum = std::accumulate(std::begin(line_ctr), std::end(line_ctr), 0);
  std::vector<std::string> files(argv+1, argv+argc);
  auto v = files | std::views::transform(count_lines);
  int sum = std::accumulate(std::begin(v), std::end(v), 0);
  std::cout << "total number of lines: " << sum << "\n";
}

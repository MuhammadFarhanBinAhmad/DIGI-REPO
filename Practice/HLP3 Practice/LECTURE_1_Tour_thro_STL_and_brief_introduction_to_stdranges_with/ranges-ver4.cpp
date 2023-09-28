// This is functional style - we care more about what should be done,
// instead of how it should be done.
// The code no longer specifies the algorithm steps that need to be
// taken, but rather how the input should be transformed in order to
// get the desired output.
// By removing the state variables and relying on the standard library
// implementation of the std::count algorithm instead of rolling your
// own, makes the code less prone to errors.
// 09/07/2021
// since parameter argc is not used, don't use -Werror flag

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

int count_lines(std::string const& file_name) {
  std::ifstream ifs{file_name};
  return std::count(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), '\n');
}

std::vector<int> count_lines_in_file(std::vector<std::string> const& files) {
  std::vector<int> results(files.size());
  std::transform(files.begin(), files.end(), results.begin(), count_lines);
  return results;
}

int main(int argc, char *argv[]) {
  std::vector<int> line_ctr = count_lines_in_file(std::vector<std::string>(argv+1, argv+argc));
  int sum = std::accumulate(std::begin(line_ctr), std::end(line_ctr), 0);
  std::cout << "total number of lines: " << sum << "\n";
}

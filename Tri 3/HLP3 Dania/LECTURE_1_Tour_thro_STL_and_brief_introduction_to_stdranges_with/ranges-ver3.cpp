// imperative programming:
// using a standard library algorithm, we're no longer concerned about
// exactly how counting is implemented; you're just declaring that
// you want to count the number of newlines that appear in the
// given input stream.
// This is idea with functional style - use abstractions that let
// you define the intent instead of specifying how to do something
// Benefits:
// 1) we've fewer state variables to worry about.
// 2) we can begin to express higher-level intent of a program
// instead of specifying the exact steps it needs to take to
// find the result.
// 3) we no longer care how the counting is implemented - the
// only task of count_lines function is to convert the input (the filename)
// to the type that std::count can understand (a pair of stream iterators).
// 09/07/2021
// since parameter argc is not used, don't use -Werror flag

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

int count_lines(std::string const& file_name) {
  std::ifstream ifs{file_name};
  return std::count(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), '\n');
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

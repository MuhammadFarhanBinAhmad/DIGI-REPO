// HLP3: 09/23/2023
// optional-extract.cpp: The following program demonstrates some abilities 
// of std::optional<> in functions with optional parameters.

#include <iostream>
#include <string>
#include <optional>

std::string extract(std::string const& text,
                    std::optional<int> start, std::optional<int> end) {
  int s{start.value_or(0)};
  int e{end.value_or(text.length())};
  return text.substr(s, e - s);
}

int main() {
  std::string substr1 = extract("sample", std::nullopt, {});
  std::cout << substr1 << '\n'; // sample

  std::string substr2 = extract("sample", 1, {});
  std::cout << substr2 << '\n'; // ample
  
  std::string substr3 = extract("sample", 1, 4);
  std::cout << substr3 << '\n'; // amp
}

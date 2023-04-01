#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "xref.hpp"

namespace {
  void test1_case();
  void test1_nocase();
  void test2_case();
  void test2_nocase();
  void test3_case();
  void test3_nocase();

  std::set<std::string> exclude_words();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
		std::cout << "Usage: ./xref.out test-number\n";
		std::cout << "Tests 1 through 5 are specified by functions listed above.\n"
							<< "Test 0 will include all the 5 tests described above.\n";
    return 0;
  }

  int const num_of_tests {6};
  int test_num{std::stoi(argv[1])};
	test_num = test_num < 0 ? 0 : test_num;
	test_num = test_num > num_of_tests ? num_of_tests : test_num;

  using TPF = void (*)();
  std::array<TPF, num_of_tests> Tests {
    test1_case,     // 1
    test1_nocase,   // 2
    test2_case,     // 3
    test2_nocase,   // 4
    test3_case,     // 5
    test3_nocase    // 6
  };

  if (test_num == 0) {
		for (TPF x : Tests) {
      x();
    }
  } else {
    Tests[test_num - 1]();
  }
}

namespace {
void test1_case() {
  std::string filename{"test1-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

void test1_nocase() {
  std::string filename{"test2-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

void test2_case() {
  std::string filename{"./input-files/test3-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

void test2_nocase() {
  std::string filename{"test4-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

void test3_case() {
  std::string filename{"test5-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

void test3_nocase() {
  std::string filename{"test6-in.txt"};
  std::string whitespace{"-;:,.?!()\"{}<>/&$@#%^*|~"};
  bool word_case{true};
  std::set<std::string> exclude = exclude_words();

  using Key = std::string;
  using Pair = std::pair<int,int>;
  using Value = std::vector<Pair>;
  std::pair<std::map<Key,Value>, int> words_pair = hlp2::xref(filename, whitespace, word_case, exclude);
  std::map<Key,Value> const& words = words_pair.first;
  int line_cnt = words_pair.second;
  std::cout << "File " << filename << " has " << line_cnt << " lines of text.\n\n";

  hlp2::print_wordmap(words);
}

  std::set<std::string> exclude_words() {
    std::set<std::string> exclude = {
      "the", "The", "A", "a", "is", "Is", "be", "Be", "it", "It", "an", "An", "can", "Can",
      "of", "Of", "do", "Do", "for", "For", "if", "If", "all", "All", "go", "Go", "but", "But",
      "we", "We", "CHAPTER", "XII", "XI", "X", "IX", "VIII", "VII", "VI", "V", "IV",
      "III", "II", "I", "and", "And", "are", "Are", "this", "This"
    };
    return exclude;
  }
} // end anonymous namespace

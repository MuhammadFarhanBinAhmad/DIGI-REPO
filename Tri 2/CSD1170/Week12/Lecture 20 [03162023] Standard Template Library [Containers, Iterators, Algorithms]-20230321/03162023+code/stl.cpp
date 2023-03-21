#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>

#if 0
template <typename T>
bool greater_than(T const& lhs, T const& rhs) {
  return lhs > rhs;
}
#else
template <typename T>
struct greater_than {
  bool operator()(T const& lhs, T const& rhs) const { return lhs > rhs; }
};
#endif

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "usage: ./a.out input-file output-file\n";
    return 0;
  }

  std::ifstream ifs{argv[1]};
  std::istream_iterator<int> iii{ifs}, eof;
  std::vector<int> vi(iii, eof);
  std::sort(std::begin(vi), std::end(vi), greater_than<int>{});
  std::vector<int>::iterator new_end = std::unique(std::begin(vi), std::end(vi));

  std::ofstream ofs{argv[2]};
  if (!ofs) {
    std::cout << "Unable to open file " << argv[2] << "\n";
    return 0;
  }
  std::ostream_iterator<int> ofi(ofs, "\n");
  std::copy(std::begin(vi), new_end, ofi);

}
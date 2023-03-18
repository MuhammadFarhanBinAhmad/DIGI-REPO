// HLP2: copy-iter.cpp [pghali@digipen.edu]
// This source file shows that ignorance [abstraction] is bliss ...
// We don't know nor care how these containers implements their iterators,
// but we're able to initialize a container with values from other
// containers just by specifying half-range of values within the source container ...

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <string>
#include <iterator>

template <typename Cont>
void print(Cont const& c, std::string const& pre, std::string const& pos="\n") {
  std::cout << pre;
  for (typename Cont::const_reference x : c) {
    std::cout << x << ' ';
  }
  std::cout << pos;
}

template <typename InIter, typename OutIter>
OutIter copy(InIter src_beg, InIter src_end, OutIter dst_beg) {
  while (src_beg != src_end) {
    *dst_beg++ = *src_beg++;
  }
  return dst_beg;
}

int main() {
  std::list<int> li{-7, 6, 7, -6, 5, -5};
  print(li, "li: ");

  // initialize vector<int> from half-range of values in list<int>
  std::vector<int> vi{li.cbegin(), li.cend()};
  print(vi, "vi: ");

  // initialize forward_list<int> with reversed half-range of values in vector<int>
  std::forward_list<int> fi{vi.rbegin(), vi.rend()};
  print(fi, "fi: ");

  // copy from list<int> to forward_list<int>
  // the :: means call the copy function defined in this file at file scope
  ::copy(li.begin(), li.end(), fi.begin());
  print(fi, "fi: ");

  // initialize deque with reversed half-range of values in list<int>
  std::deque<int> di{li.rbegin(), li.rend()};
  print(di, "di: ");

  // copy from vector<int> to deque<int>
  ::copy(vi.begin(), vi.end(), di.begin());
  print(di, "di: ");
  
  // initialize set<int> with elements from deque<int>
  std::set<int> si(di.begin(), di.end());
  print(si, "si: ");

  // initialize vector<char>:
  std::string singapore{"singapore"};
  std::vector<char> vc{singapore.begin(), singapore.end()};
  print(vc, "vc: ");
  // now we want to sort these characters ...
  std::set<char> sc{vc.begin(), vc.end()};
  print(sc, "sc: ");

  // copy from set<char> to vector<char>
  ::copy(sc.begin(), sc.end(), vc.begin());
  print(vc, "vc: ");
}

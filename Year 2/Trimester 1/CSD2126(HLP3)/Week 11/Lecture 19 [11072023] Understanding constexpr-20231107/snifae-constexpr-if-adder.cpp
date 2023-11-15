#include <iostream>
#include <string>
#include <vector>

template <bool, typename T=void>
struct my_enable_if {};

template <typename T>
struct my_enable_if<true,T> { using type = T; };

template <bool B, typename T=void>
using my_enable_if_t = typename my_enable_if<B,T>::type;

template <typename T>
class Adder {
public:
  Adder(T t) : val{t} {}

#if 1
  template <typename U>
  my_enable_if_t<!std::is_same_v<T,std::vector<U>>,T>
  add(U u) const { return val+u; }

  template <typename U>
  my_enable_if_t<std::is_same_v<T,std::vector<U>>,T>
  add(U u) const {
    T cp{val};
    for (auto& x : cp) { x += u; }
    return cp;
  }
#else
  template <typename U>
  T add(U u) const {
    if constexpr(!std::is_same_v<T,std::vector<U>>) { return val+u; }
    else if constexpr(std::is_same_v<T,std::vector<U>>) {
      T cp{val};
      for (auto& x : cp) { x += u; }
      return cp;
    }
  }
#endif
private:
  T val;
};


#if 0
template <typename T>
class Adder {
public:
  Adder(T t) : val{t} {}
  template <typename U>
  T add(U u) const { return val+u; }
private:
  T val;
};

template <typename T>
class Adder<std::vector<T>> {
public:
  Adder(std::vector<T> t) : val{t} {}
  
  template <typename U>
  std::vector<T> add(U u) const {
    std::vector<T> cp{val};
    for (auto& x : cp) { 
      x += u;
    }
    return cp;
  }
private:
  std::vector<T> val;
};
#endif

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& rhs) {
  for (T const& x : rhs) { os << x << ' '; }
  return os;
}

int main() {
  Adder<int> ai(4);
  //std::cout << "ai.add(5.2): " << ai.add(5) << '\n';
  std::cout << "ai.add(5.2): " << ai.add(5.2) << '\n';

  Adder<std::string> as{std::string{"hello "}};
  std::cout << "as.add(\"world\"): " << as.add("world") << '\n';

  Adder<std::vector<int>> avi{std::vector<int>{1,2,3,4,5}};
  std::cout << "avi.add(4): " << avi.add(4) << '\n';
}
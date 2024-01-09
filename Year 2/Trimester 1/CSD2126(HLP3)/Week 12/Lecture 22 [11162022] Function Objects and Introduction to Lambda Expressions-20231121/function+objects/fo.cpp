#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

// a functin object that returns true if x > N
struct GTN {
  GTN(int n) : N{n} {}
  bool operator()(int x) const { return x > N; }
  int N;
};



int global_var = 1;
bool gtn_func(int x) { return x > global_var; }




int main() {
  int func_var = 1;
  auto GTN_lam = [&func_var](int x) -> bool { return x > func_var; };
  std::vector<int> vi{1, 2, 3, 4, 5, 6};
  std::cout << std::count_if(vi.begin(), vi.end(), GTN(3)) << "\n";
  std::cout << std::count_if(vi.begin(), vi.end(), 
       [](int x) { return x > 1; }) << "\n";
  func_var = global_var = -1;
  std::cout << std::count_if(vi.begin(), vi.end(), GTN_lam) << "\n";
  std::cout << std::count_if(vi.begin(), vi.end(), gtn_func) << "\n";

  std::function<bool (int)> func0 = gtn_func;
  std::cout << std::count_if(vi.begin(), vi.end(), func0) << "\n";
  std::function<bool (int)> func1 = GTN_lam;
  std::cout << std::count_if(vi.begin(), vi.end(), func1) << "\n";

  std::vector<std::function<bool(int)>> vf{func0, func1};
  std::cout << std::count_if(vi.begin(), vi.end(), vf[0]) << "\n";
  std::cout << std::count_if(vi.begin(), vi.end(), vf[1]) << "\n";
  
}

#if 0

double fin_diff(double f(double), double x, double h) {
  return (f(x+h) - f(x))/h;
}

double sac_f(double x) {
  return std::sin(x) + std::cos(x);
}

template <typename T>
constexpr T pi{3.141'592'653'589'793'238'462'643'383'279L};

int main() {
  std::cout << fin_diff(sac_f, pi<double>/2.0, 0.001) << "\n";
}
#endif
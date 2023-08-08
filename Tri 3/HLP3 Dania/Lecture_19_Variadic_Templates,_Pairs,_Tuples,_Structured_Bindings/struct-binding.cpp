// CSD2125 11/06
// Structured bindings make it easier to access one or more elements
// of a tuple ...
#include <iostream>
#include <string>
#include <tuple>
#include <initializer_list>

using namespace std::string_literals;  // "..."s

std::tuple<std::string, int, bool> make_saturn() { 
  return std::tuple{"Saturn"s, 82, true};
}

auto make_earth() {
  struct Planet { std::string name; int n_moons; bool rings; };
  return Planet {"Earth", 1, false}; 
}

#if 1
int main() {
/*
Using structured bindings, multiple variables can be initialized at once
using auto and a bracket declaration list. As with the auto keyword in general,
you can apply control over whether the variables should be mutable references,
forward references, const references, or values by using the corresponding modifier.
*/
  auto const& [name, n_moons, rings] = make_saturn();
  std::cout << name << ' ' << n_moons << ' ' << rings << '\n';

// Can also be used to extract the individual members of a tuple in a for-loop
  auto planets = { 
    std::tuple{"Mars"s, 2, false}, 
    std::tuple{"Neptune"s, 14, true} 
  };
  
  for (auto const& [name, n_moons, rings] : planets) { 
    std::cout << name << ' ' << n_moons << ' ' << rings << '\n'; 
  }

// Structured bindings also work with structures
  auto p = make_earth(); 
  std::cout << p.name << ' ' << p.n_moons << ' ' << p.rings << '\n';

  auto [ename, enum_moons, ehas_rings] = make_earth();
  std::cout << ename << ' ' << enum_moons << ' ' << ehas_rings << '\n';
}
#else // without structured bindings

int main() {
  { // Using std::get<N>()
    auto t = make_saturn();
    auto name = std::get<0>(t);
    auto n_moons = std::get<1>(t);
    auto rings = std::get<2>(t);
    std::cout << name << ' ' << n_moons << ' ' << rings << '\n';
    // Output: Saturn 82 true
    
  }
  { // Using std::tie()
    std::string name = std::string{};
    int n_moons = int{};
    bool rings = bool{};
    std::tie(name, std::igonore, rings) = make_saturn();
    ++n_moons;
    std::cout << name << ' ' << n_moons << ' ' << rings << '\n';
  }
}
#endif

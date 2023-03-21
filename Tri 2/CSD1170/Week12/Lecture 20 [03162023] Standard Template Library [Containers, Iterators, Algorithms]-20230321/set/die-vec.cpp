/*
Suppose we've a six-sided die. We roll the die, then record what number
we rolled. We then keep rolling the die and record what number came up,
and keep repeating this process. The question is: how many times, on average,
will we roll the die before the same number comes up twice?
Here, we solve a simulation that records the numbers obtained by rolling
the die in a std::vector<int>.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// roll six-sided die and return number that came up
int roll_die() {
  return (std::rand() % 6) + 1;
}

// keep rolling the dice until a number appears twice, then
// reorts the number of die rolls
size_t run_simulation() {
  std::vector<int> generated;

  while (true) {
    int next_value = roll_die();

    // check if this value has come up before.
    // if so, return the number of rolls required to obtain the value twice:
    // number of dice rolled so far + plus one for this roll
    for (size_t k{}; k < generated.size(); ++k) {
      if (generated[k] == next_value) {
        return generated.size() + 1;
      }
    }
    // otherwise, remember this die roll
    generated.push_back(next_value);
  }
}

// run simulation ...
int main() {
  std::srand(static_cast<size_t>(std::time(NULL)));

  constexpr size_t max_iterations {1'000UL};
  size_t total{};
  for (size_t k{}; k < max_iterations; ++k) {
    total += run_simulation();
  }

  // report the result ...
  std::cout << "Average number of steps: " << static_cast<double>(total)/max_iterations << "\n";
}
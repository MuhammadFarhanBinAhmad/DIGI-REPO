// CSD2125 11/09
// Performance comparison between lambda and function wrapped in std::function<>

#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <functional>

class Timer {
public:
  Timer() : start_time(std::chrono::steady_clock::now()), end_time(start_time) {}
  void Start() { start_time = std::chrono::steady_clock::now(); }
  void End()   { end_time   = std::chrono::steady_clock::now(); }
  std::chrono::steady_clock::time_point Start() const { return start_time; }
  std::chrono::steady_clock::time_point End()   const { return end_time; }
private:
// the two main entities are:
// duration: of time is a specific number of ticks over a time unit. One example
// is a duration such as "3 minutes" or 86,400 seconds (1 day).
// time_point: representing a combination of a duration and a beginning of
// time. A typical example of time_point is "NY Midnight 2000" which is
// described as 1,262,300,400 seconds since January 1, 1970.
// duration and time_point can be added, subtracted, and scaled. For example,
// we can add a duration to a time_point to send a message that we will be
// home in 2 hours.
// steady_clock is a clock with guaranteed increasing time points and is
// therefore convenient for a timer.
  std::chrono::steady_clock::time_point start_time, end_time;
};

std::ostream& operator<<(std::ostream& os, Timer const& rhs) {
  std::chrono::steady_clock::duration exec_time = rhs.End() - rhs.Start();

  os << "Time taken in secs: " << std::fixed << std::setprecision(2) << std::setw(5)
  // for printing something more tangible, let's print the seconds taken by
  // determining milliseconds and divide this by the double value 1000.0
    << std::chrono::duration_cast<std::chrono::milliseconds>(exec_time).count()/1000.0
    << " | millisecs: " << std::setw(6) 
    << std::chrono::duration_cast<std::chrono::microseconds>(exec_time).count()/1000.0
    //<< " | microsecs: " << std::setw(12) 
    //<< std::chrono::duration_cast<std::chrono::nanoseconds>(exec_time).count()/1000.0
    << "\n";
  return os;
}

void use_lambda();
void use_function();

// driver program
int main() { 
  use_lambda();
  use_function();
}

// test time taken by lambdas
void use_lambda() {
  Timer t;

  auto lambda = [](int v) { return 3*v; };
  using T = decltype(lambda);
  auto fs = std::vector<T>(10'000'000, lambda);
  auto res = 1;
  t.Start(); // start timer
  for (const auto& f: fs) {
    res = f(res);
  }

  t.End();   // end timer
  std::cout << "lambda  : " << t; // left-shift operator is overloaded for class Timer
}

// time taken by same lambda which is now wrapped in polymorphic std::function<>
void use_function() {
  Timer t;

  auto lambda = [](int v) { return 3*v; };
  using T = std::function<int(int)>;
  auto fs = std::vector<T>(10'000'000, T{lambda});
  auto res = 1;
  t.Start(); // start timer
  for (const auto& f: fs) {
    res = f(res);
  }

  t.End();   // end timer
  std::cout << "function: " << t; // left-shift operator is overloaded for class Timer
}

// HLP2: 09/16/2020
// simple finite state machine to illustrate function pointers

#include <iostream>

auto get_input() -> char {
  std::cout << "enter character: ";
  char ch;
  std::cin >> ch;
  return ch;
}

struct State {
  int data;
  //void (*next)(State*);
  using PTR_STATE_FUNC = auto (*)(State*) -> void;
  PTR_STATE_FUNC next;
};

// functions that define certain states for an animated character ...
auto stand(State*) -> void;
auto walk(State*) -> void;
auto run(State*) -> void;
auto jump(State*) -> void;

auto stand(State *state) -> void {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
#if 1
  State::PTR_STATE_FUNC pf;
  switch(value) {
    case 'j': pf = jump; break;
    case 'w': pf = walk; break;
    default:  pf = nullptr;
  }
  state->next = pf;
#else
  state->next = ('a' == value) ? walk : jump;
#endif
}

auto walk(State *state) -> void {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  state->next = ('r' == value) ? run : jump;
}

auto run(State *state) -> void {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  if ('j' == value) {
    state->next = jump;
  }
}

auto jump(State *state) -> void {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  if ('s' == value) {
    state->next = stand;
  }
}

auto main() -> int {
  State s{1, stand};
  while (s.next) {
    s.next(&s);
  }
  std::cout << "character is dead!!!\n";
}

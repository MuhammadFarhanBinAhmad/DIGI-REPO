// simple finite state machine to illustrate function pointers
// CSD2125
// 09/16
#include <iostream>

char get_input() {
  std::cout << "enter character: ";
  char ch;
  std::cin >> ch;
  return ch;
}

struct State {
  int data;
  void (*next)(State*);
};

void stand(State*);
void walk(State*);
void run(State*);
void jump(State*);

void stand(State *state) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  state->next = ('a' == value) ? walk : jump;
}

void walk(State *state) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  state->next = ('b' == value) ? run : jump;
}

void run(State *state) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  if ('c' == value) {
    state->next = jump;
  }
}

void jump(State *state) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  char value = get_input();
  if ('e' == value) {
    state->next = stand;
  }
}

int main() {
  State s{1, stand};
  while (s.next) {
    s.next(&s);
  }
}

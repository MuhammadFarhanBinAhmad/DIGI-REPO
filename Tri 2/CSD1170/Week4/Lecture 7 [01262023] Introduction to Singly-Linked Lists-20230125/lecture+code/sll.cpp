/*
HLP2: sll.cpp
01/29/2022

This program illustrates a very simple interface to a singly-linked list.
Code for insertions (push_front and push_back) and iterations thro' the list
(size and print) are shown.
*/
#include <iostream>

struct node {
  int data;
  node *next;
};

namespace {
  void push_back(node**, int);
  void push_front(node**, int);
  size_t size(node const*);
  void print(node const*);
}

int main() {
  node *head{nullptr};

  std::cout << "size: " << size(head) << '\n';
  push_front(&head, -10);
  push_front(&head, -3);
  push_front(&head, -15);
  push_front(&head, -8);
  std::cout << "size: " << size(head) << '\n';

  push_back(&head, 10);
  push_back(&head, 3);
  push_back(&head, 15);
  push_back(&head, 8);
  
  std::cout << "size: " << size(head) << '\n';

  print(head);
}

namespace {
void push_back(node **ptr_head, int elem) {
  node *new_node{new node{elem, nullptr}};
  if (*ptr_head == nullptr) {
    *ptr_head = new_node;
    return;
  }

  // get to end of linked list
  node *last_node{*ptr_head};
  while (last_node->next) {
    last_node = last_node->next;
  }
  last_node->next = new_node;
}

void push_front(node **ptr_head, int value) {
  node *new_node {new node{value, nullptr}};

  if (*ptr_head) {
    new_node->next = *ptr_head;
  }
  *ptr_head = new_node;
}

size_t size(node const *head) {
  size_t count{};
  for (node const *curr_node = head; curr_node; curr_node = curr_node->next) {
    ++count;
  }
  return count;
}

void print(node const *head) {
  for (node const *curr_node = head; curr_node; curr_node = curr_node->next) {
    std::cout << curr_node->data << ' ';
  }
  std::cout << "\n";
}
} // end anonymous namespace

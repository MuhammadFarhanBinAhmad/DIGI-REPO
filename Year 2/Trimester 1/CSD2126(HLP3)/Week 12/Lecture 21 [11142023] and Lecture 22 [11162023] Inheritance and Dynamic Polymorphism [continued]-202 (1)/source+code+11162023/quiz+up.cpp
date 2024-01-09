// HLP3: quiz+up.cpp
// 11/05/2023
// Illustrates the use of std::unique_ptr<> to encapsulate pointers to base class IQuestion
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "question+up.h"

class Quiz {
public:
  static std::unique_ptr<IQuestion> make_question(std::vector<std::unique_ptr<IQuestion>>::const_iterator);
public:
  //Quiz(std::istream&); // read from file ...
  Quiz(std::vector<std::unique_ptr<IQuestion>> const&);
  Quiz(Quiz const& rhs);
  ~Quiz() = default;
  Quiz& operator=(Quiz const&);
  
  void process() const;
private:
  std::list<std::unique_ptr<IQuestion>> slate;
};

std::unique_ptr<IQuestion> Quiz::make_question(std::vector<std::unique_ptr<IQuestion>>::const_iterator cit) {
  return (*cit)->clone();
}

Quiz::Quiz(std::vector<std::unique_ptr<IQuestion>> const& rhs) {
  std::vector<std::unique_ptr<IQuestion>>::const_iterator first = std::cbegin(rhs), last = std::cend(rhs);
  while (first != last) {
    slate.push_back(make_question(first));
    ++first;
  }
}

Quiz::Quiz(Quiz const& rhs) {
  for (std::unique_ptr<IQuestion> const& p : rhs.slate) {
    slate.push_back(p->clone());
  }
}

Quiz& Quiz::operator=(Quiz const& rhs) {
  Quiz cp{rhs};
  slate.clear();
  for (std::unique_ptr<IQuestion> const& p : cp.slate) {
    slate.push_back(p->clone());
  }
  return *this;
}

void Quiz::process() const {
  for (std::unique_ptr<IQuestion> const& p : slate) {
#if 0
    p->ask(std::cout);
#else
    p->display(std::cout);
    std::cout << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    std::cout << (p->check_answer(response) ? "Correct\n" : "Wrong\n");
  }
#endif
}

std::vector<std::unique_ptr<IQuestion>> make_quiz();

int main() {
#if 1
  Quiz q1{make_quiz()};
  q1.process();
#else
  int your_score{0};
  for (std::unique_ptr<IQuestion> const& p : quiz) {
    p->display(std::cout);
    std::cout << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    your_score += p->check_answer(response) ? 1 : 0;
    std::cout << (p->check_answer(response) ? "Correct" : "Wrong") << '\n';
  }
  std::cout << "Your grade is: " <<
            (static_cast<double>(your_score)*100.0)/static_cast<double>(quiz.size()) << '\n';
#endif
}

std::vector<std::unique_ptr<IQuestion>> make_quiz() {
  std::vector<std::unique_ptr<IQuestion>> quiz;
  quiz.push_back(std::make_unique<ChoiceQuestion>(
    "In what country was the inventor of C++ born", std::to_string(6),
    std::vector<std::string>{"Singapore", "USA", "China", "India", "Sweden", "Denmark"}));
  quiz.push_back(std::make_unique<ChoiceQuestion>(
    "Which of the following are the best cities in the world?", std::to_string(4),
    std::vector<std::string>{"Singapore", "Vancouver", "Seattle", "All of the above"}));

  quiz.push_back(std::make_unique<TrueFalseQuestion>("C++ condition operator evaluates to lvalue.", "true"));
  quiz.push_back(std::make_unique<TrueFalseQuestion>(
    "In C++, pure virtual functions cannot have definitions", "false"));

  quiz.push_back(std::make_unique<ShortAnswerQuestion>("Who invented C++?", "Bjarne Stroustrup"));
  quiz.push_back(std::make_unique<ShortAnswerQuestion>(
    "Which C++ operator requires three operands", "Condition operator"));

  return quiz;
}
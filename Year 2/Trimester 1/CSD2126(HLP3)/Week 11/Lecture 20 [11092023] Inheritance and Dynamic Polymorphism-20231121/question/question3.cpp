// HLP3: question3.cpp
// 11/09/2023
// To avoid the slicing problem when accessing different classes in a
// class hierarchy, we must use pointers.
// Pointers to the various objects all have the same size - namely, the
// size of a memory address - even though the objects themselves may
// have different sizes ...
// However, the problem is that we have an object of type Question* that
// is unable to use the type of the object that it points to [Question or
// ChoiceQuestion] to determine which overridden function display() to be
// invoked. Instead, the pointer always invokes Question::display() ...

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// base class [short answer question]
class Question {
public:
  Question() = default;
  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  void display() const { std::cout << text << '\n'; }
private:
  std::string text;
  std::string answer;
};

// derived class [multiple-choice question]
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion() = default;
  void add_choice(std::string const& choice, bool correct);
  void display() const;
private:
  std::vector<std::string> choices;
};

void ChoiceQuestion::add_choice(std::string const& choice, bool correct) {
  choices.emplace_back(choice);
  if (correct) {
    std::string choice_str = std::to_string(choices.size());
    set_answer(choice_str);
  }
}

void ChoiceQuestion::display() const {
  Question::display();
  std::vector<std::string>::size_type i{};
  for (std::string const& x : choices) {
    std::cout << ++i << ": " << x << '\n';
  }
}

int main() {
  // set a basic question ...
  Question q, *pbq{&q};
  pbq->set_text("Who was the inventor of C++?");
  pbq->set_answer("Bjarne Stroustrup");

  // set a choice question ...
  ChoiceQuestion cq, *pcq{&cq};
  pcq->set_text("In which country was the inventor of C++ born?");
  pcq->add_choice("Singapore", false); pcq->add_choice("USA", false);
  pcq->add_choice("China", false);     pcq->add_choice("India", false);
  pcq->add_choice("Sweden", false);    pcq->add_choice("Denmark", true);

  // create a quiz ...
  int const quiz_size{2};
  Question *quiz[quiz_size];
  quiz[0] = pbq;
/*
Note that a derived-class pointer can be converted to a base class pointer.
This is perfectly legal. A pointer is the starting address of an object.
Because every ChoiceQuestion is a special case of a Question, the starting
address of a ChoiceQuestion object is, in particular, the starting address of a
Question object. The reverse assignment - from a base-class pointer to a
derived-class pointer - is an error.
*/
  quiz[1] = pcq;

  // make student take the quiz ...
  for (int i{}; i < quiz_size; ++i) {
    // quiz[i] evaluates to Question*.
    // quiz[i]->display() will invoke Question::display()
    // what we really want is for quiz[i]->display() to invoke Question::display()
    // when quiz[i] is pointing to an object of type Question and to invoke
    // ChoiceQuestion::display() when quiz[i] is pointing to an object of type ChoiceQuestion!!!
    quiz[i]->display();
    std::cout << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    std::cout << (quiz[i]->check_answer(response) ? "Correct answer\n" : "Wrong answer\n");
  }
}

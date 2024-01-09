// HLP3: question4.cpp
// 11/09/2023
// In question4a.cpp, we declared in base class Question a virtual function
// Question::display() and we declared an overriding function 
// ChoiceQuestion::display() in derived class ChoiceQuestion. This virtual
// overloading is what made dynamic binding possible: the ability to invoke
// through a base class pointer a virtual function overriden by a derived
// classs. For overriding to occur, several requirements must be met:
// a) The base class function must be virtual.
// b) The base and derived function names must be virtual [except in case of dtors].
// c) The parameters of the base and derived functions must be identical.
// d) The costness of the base and derived functions must be identical.
// e) The return types of the base and derived functions must be identical.
// f) The reference qualifiers of the base and derived functions must be identical.
//
// All these requirements for overriding mean that its is possible for
// programmers to make small mistakes. These mistakes lead them to think they've
// overridden a base class virtual function but instead they may have declared
// a new virtual function that can be overriden by classes that inherit from the
// derived class. And, sometimes you can't rely on compilers notifying you if you
// make these small mistakes.
//
// Because declaring derived class overrides is important to get right, but easy to
// get wrong, C++11 provides the override specifier for you to make explicit that a 
// derived class function is supposed to override a base class version. We use this
// specifier when Question::display() is overridden in ChoiceQuestion::display().

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// base class [short answer question type]
class Question {
public:
  Question() = default;
  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  virtual void display() const { std::cout << text << '\n'; }
private:
  std::string text;
  std::string answer;
};

// derived class [multiple-choice question type]
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion() = default;
  void add_choice(std::string const& choice, bool correct);
// if you remove the const in both the declaration and definition and then
// recompile, the compiler will use the override specifier to let you know
// that this display() is not overriding Question::display().
  virtual void display() const override;
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
  Question *pbq = new Question;
  pbq->set_text("Who was the inventor of C++?");
  pbq->set_answer("Bjarne Stroustrup");

  // set a choice question ...
  ChoiceQuestion *pcq = new ChoiceQuestion;
  pcq->set_text("In which country was the inventor of C++ born?");
  pcq->add_choice("Singapore", false); pcq->add_choice("USA", false);
  pcq->add_choice("China", false);     pcq->add_choice("India", false);
  pcq->add_choice("Sweden", false);    pcq->add_choice("Denmark", true);

  // create a quiz ...
  int const quiz_size{2};
  Question *quiz[quiz_size];
  quiz[0] = pbq;
  quiz[1] = pcq;

  // make student take the quiz ...
  for (int i{}; i < quiz_size; ++i) {
    // quiz[i] evaluates to Question*.
    // quiz[i]->display() will invoke Question::display()
    // what we really want is for quiz[1]->display() to invoke ChoiceQuestion::display()!!!
    quiz[i]->display();
    std::cout << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    std::cout << (quiz[i]->check_answer(response) ? "Correct answer\n" : "Wrong answer\n");
  }

  // don't forget to release memory ...
  for (int i{}; i < quiz_size; ++i) {
    delete quiz[i];
  }

  // but we still have memory leaks ...
}

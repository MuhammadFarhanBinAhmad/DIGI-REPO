// HLP3: question5.cpp
// 11/09/2023
// First, we fix memory leaks by declaring the base class destructor virtual.
// Second, we enhance the quiz [which currently consists of a base class modeling
// short-answer questions and a derived class modeling multiple-choice
// questions] with the ability to provide true/false questions. We derive
// class TrueFalseQuestion from base class Question. This results in a three
// class hierarchy consisting of a root base class Question and two derived
// classes ChoiceQuestion and TrueFalseQuestion.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// base class [short answer question type]
class Question {
public:
  Question()          { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  virtual ~Question() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  virtual void display() const { std::cout << text << '\n'; }
private:
  std::string text;
  std::string answer;
};

/*
Since true/false questions are short-answer questions [where answers are the
strings "true" or "false"], we can reuse the interface of base class Question.
This is nice because we can separate the concepts of short-answer and true/false
questions without having to rewrite much code ...
*/
// true/false question type ...
class TrueFalseQuestion : public Question {
public:
  TrueFalseQuestion()          { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  virtual ~TrueFalseQuestion() override { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

// multiple-choice question type ...
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion()  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  // even though we don't specify this dtor as virtual, it is a virtual
  // function since the base class dtor is a virtual function ...
  ~ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
  
  void add_choice(std::string const& choice, bool correct);
  virtual void display() const override; // could have been declared as: void display
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
  std::vector<Question*> quiz; // create a quiz ...

  // add a true/false question ...
  Question *ptf = new TrueFalseQuestion;
  ptf->set_text("C++ condition operator evaluates to lvalue.");
  ptf->set_answer("true");
  quiz.emplace_back(ptf); // add this true/false question to the quiz ...

  // set a basic question ...
  Question *pbq = new Question;
  pbq->set_text("Who was the inventor of C++?");
  pbq->set_answer("Bjarne Stroustrup");
  quiz.emplace_back(pbq); // add this base question to the quiz ...

  // set a choice question ...
  ChoiceQuestion *pcq = new ChoiceQuestion;
  pcq->set_text("In which country was the inventor of C++ born?");
  pcq->add_choice("Singapore", false); pcq->add_choice("USA", false);
  pcq->add_choice("China", false);     pcq->add_choice("India", false);
  pcq->add_choice("Sweden", false);    pcq->add_choice("Denmark", true);
  quiz.emplace_back(pcq); // add this multiple-choice question to the quiz ...

  // make student take the quiz ...
  for (auto const *p : quiz) {
    p->display();
    std::cout << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    std::cout << (p->check_answer(response) ? "Correct answer\n" : "Wrong answer\n");
  }

  // don't forget to release memory ...
  for (auto *p : quiz) { //}; i < quiz_size; ++i) {
    delete p;
  }
}

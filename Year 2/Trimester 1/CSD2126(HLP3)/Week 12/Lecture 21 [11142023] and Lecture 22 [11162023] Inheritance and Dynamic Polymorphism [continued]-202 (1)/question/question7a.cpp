// HLP3: question7a.cpp
// 11/09/2023
// Question::operator=() is now a protected function. It is now possible to
// correcly define copy-assignment functions in derived classes. However, it
// is still not possible for client to assign between Question objects.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

// base class [short answer question type]
class IQuestion {
protected:
  IQuestion& operator=(IQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    text=rhs.text; answer=rhs.answer; 
    return *this;
  }
public:
  IQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  virtual ~IQuestion() = 0; 
  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  virtual void display() const { std::cout << text << '\n'; }
private:
  std::string text;
  std::string answer;
};

IQuestion::~IQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

// short-answer question type ...
class ShortAnswerQuestion : public IQuestion {
public:
  ShortAnswerQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ShortAnswerQuestion& operator=(ShortAnswerQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    IQuestion::operator=(rhs);
    return *this;
  }
  virtual ~ShortAnswerQuestion() override { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
};

// true/false question type ...
class TrueFalseQuestion : public IQuestion {
public:
  TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  TrueFalseQuestion& operator=(TrueFalseQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    IQuestion::operator=(rhs);
    return *this;
  }
  virtual ~TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
};

// multiple-choice question type ...
class ChoiceQuestion : public IQuestion {
public:
  ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ChoiceQuestion& operator=(ChoiceQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    IQuestion::operator=(rhs); // call base class operator= function
    choices = rhs.choices; // copy ChoiceQuestion subobject members
    return *this;
  }
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
  IQuestion::display();
  std::vector<std::string>::size_type i{};
  for (std::string const& x : choices) {
    std::cout << ++i << ": " << x << '\n';
  }
}

int main() {
  // add a true/false question ...
  TrueFalseQuestion tfq1, tfq2;
  tfq1.set_text("C++ condition operator evaluates to lvalue.");
  tfq1.set_answer("true");
  
  // another true/false question ...
  tfq2.set_text("In C++, pure virtual functions cannot have definitions.");
  tfq2.set_answer("false");

  // set a short-answer question ...
  ShortAnswerQuestion sq1, sq2;
  sq1.set_text("Who was the inventor of C++?");
  sq1.set_answer("Bjarne Stroustrup");

  // another short-answer question ...
  sq2.set_text("Which C++ operator requires three operands?");
  sq2.set_answer("Condition operator");

  // set a choice question ...
  ChoiceQuestion cq1, cq2;
  cq1.set_text("In which country was the inventor of C++ born?");
  cq1.add_choice("Singapore", false); cq1.add_choice("USA", false);
  cq1.add_choice("China", false);     cq1.add_choice("India", false);
  cq1.add_choice("Sweden", false);    cq1.add_choice("Denmark", true);

  // set another question ...
  cq2.set_text("Which of the following are the best cities in the world?");
  cq2.add_choice("Singapore", false); cq2.add_choice("Vancouver", false);
  cq2.add_choice("Seattle", false);   cq2.add_choice("All of the above", true);
std::cout << "-------------------------------------------\n";

  sq1  = sq2;  // ok: assignment between like objects
  tfq1 = tfq2; // ok: assignment between like objects
  cq1  = cq2;  // ok: assignment between like objects
std::cout << "-------------------------------------------\n";

#if 0
  *pq1 = *pq2; // error: Question::operator=() is protected
  pq1->display();
  pq2->display();
std::cout << "-------------------------------------------\n";
#endif
}

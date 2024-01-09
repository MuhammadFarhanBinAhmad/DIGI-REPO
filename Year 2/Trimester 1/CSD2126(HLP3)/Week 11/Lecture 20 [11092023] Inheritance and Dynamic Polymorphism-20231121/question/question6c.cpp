// HLP3: question6c.cpp
// 11/09/2023
// We provide conventional copy-assignment functions for derived classes in the
// inheritance hierarchy. The addition of these functions avoid the need for
// dynamic_cast when assigning like objects, that is for assignments between
// TrueFalseQuestion objects and assignments between TChoiceQuestion objects.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <exception>

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

// base class [short answer question type]
class Question {
public:
  Question() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  virtual Question& operator=(Question const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    text=rhs.text; answer=rhs.answer; 
    return *this;
  }
  virtual ~Question() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  virtual void display() const { std::cout << text << '\n'; }
private:
  std::string text;
  std::string answer;
};

// true/false question type ...
class TrueFalseQuestion : public Question {
public:
  TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  // usual copy-assignment is implicitly generated but explicitly derived
  // here for explanatory reasons ...
  TrueFalseQuestion& operator=(TrueFalseQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    Question::operator=(rhs);
    return *this;
  }

  virtual TrueFalseQuestion& operator=(Question const& rhs) override {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return operator=(dynamic_cast<TrueFalseQuestion const&>(rhs));
  }
  virtual ~TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
};

// multiple-choice question type ...
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  // usual copy-assignment is implicitly generated but explicitly derived
  // here for explanatory reasons ...
  ChoiceQuestion& operator=(ChoiceQuestion const& rhs) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    Question::operator=(rhs); // call base class operator= function
    choices = rhs.choices; // copy ChoiceQuestion subobject members
    return *this;
  }

  virtual ChoiceQuestion& operator=(Question const& rhs) override {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return operator=(dynamic_cast<ChoiceQuestion const&>(rhs));
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
  Question::display();
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

  // set a basic question ...
  Question q1, q2;
  q1.set_text("Who was the inventor of C++?");
  q1.set_answer("Bjarne Stroustrup");

  // another basic question ...
  q2.set_text("Which C++ operator requires three operands?");
  q2.set_answer("Condition operator");

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

  Question *pq1 = &cq1, *pq2 = &cq2;
  
  // use virtual ChoiceQuestion::operator=(Question const&)
  *pq1 = *pq2;
  pq1->display();
  pq2->display();
std::cout << "-------------------------------------------\n";

  // use non-virtual ChoiceQuestion::operator=(ChoiceQuestion const&);
  cq1 = cq2;
std::cout << "-------------------------------------------\n";
  
  // check for mixed-assignments ...
  try {
    Question *pq3 = &tfq1, *pq4 = &cq2;
    // here, again CheckQuestion's operator= is invoked. However, the downcast of
    // a reference to Question to a reference to CheckQuestion fails [because the
    // actual object is a TrueFailQuestion] and a std::bad_cast exception is thrown
    *pq4 = *pq3;
  } catch (std::bad_cast const& e) {
    std::cout << e.what() << '\n';
  }
std::cout << "-------------------------------------------\n";
}

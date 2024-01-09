// HLP3: question6a.cpp
// 11/09/2023
// So far, we've software that deals with question types for quizzes. Most
// questions need the question's text, answer, a way to display the text, and
// a way to check if the provided answer is correct or incorrect.
// It is possible that we might want to assign a question to another and we
// do that by adding copy-assignment functions for all inheritance classes.
// Note that copy-assignment will be synthesized by the compiler in our simple
// types. However, we're using the copy-assignment function as a proxy for other
// functions that you will implement for these inheritance types.
// The code below shows examples of partial and mixed assignments ...

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

// base class [short answer question type]
class Question {
public:
  Question() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  Question& operator=(Question const& rhs) { // note: could be synthesized by compiler
    text=rhs.text; answer=rhs.answer; 
    std::cout << __PRETTY_FUNCTION__ << '\n';
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
  TrueFalseQuestion& operator=(TrueFalseQuestion const& rhs) { // could be synthesized by compiler ... 
    Question::operator=(rhs); // call base class operator= function ...
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
  virtual ~TrueFalseQuestion() override { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
};

// multiple-choice question type ...
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
  ChoiceQuestion& operator=(ChoiceQuestion const& rhs) { // could be synthesized by compiler ...
    Question::operator=(rhs); // call base class operator= function ...
    choices = rhs.choices;
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return *this;
  }
  ~ChoiceQuestion() override { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
  
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

  // assignment of like types works correctly ...
  Question q3; TrueFalseQuestion tfq3; ChoiceQuestion cq3;
  tfq3 = tfq2; tfq3.display();
  cq3  = cq2;  cq3.display();
  q3   = q2;   q3.display();
std::cout << "-------------------------------------------\n";

  // perform assignment of like types through pointers to base class type ...
  ChoiceQuestion cq4; 
  Question *pq1 = &cq4, *pq2 = &cq2;
  *pq1 = *pq2; // problem: partial assignment!!!
// The problem here is that the assignment operator invoked is that of Question class,
// even though the objects are of type ChoiceQuestion. As a result, only the Question
// part of cq4 will be assigned causing a partial assignment: only the Question part
// of cq4 will have values from cq2, but cq4's ChoiceQuestion members remain unchanged.
  pq1->display(); pq2->display();
std::cout << "-------------------------------------------\n";

  Question *pq3 = &tfq3, *pq4 = &cq2;
  *pq3 = *pq4; // problem: mixed assignment!!!
// This is a mixed-type assignment: a TrueFalseQuestion is on the left and a ChoiceQuestion
// is on the right. Mixed-type assignments aren't usually a problem in a strongly typed
// language such as C++. However, because Question::operator= is invoked, it is
// assigning the Question subobject of a ChoiceQuestion object to the Question subobject
// of a TrueFalseQuestion object.
std::cout << "-------------------------------------------\n";
}

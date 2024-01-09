// HLP3: question6b.cpp
// 11/09/2023
// In question6a.cpp, we added copy-assignment function to all classes in the
// inheritance hierarchy that caused partial and mixed assignments when using
// pointers to base classes to assign derived type objects.
// One way to solve the partial assignment problem is to make the assignment
// operators virtual. Unfortunately, this comes causes a compile-time error
// in class ChoiceQuestion since language rules require the virtual copy-
// assignment function to have identical parameter types in all classes of
// the inheritance hierarchy:
// class Question {
// public:
//   virtual Question& operator=(Question const& rhs);
// ...
// };
//
// class ChoiceQuestion {
// public:
//   virtual ChoiceQuestion& operator=(Question const& rhs);
// ...
// };
//
// When ChoiceQuestion::operator= is invoked, the parameter rhs cannot be used to
// access the members of the ChoiceQuestion subobject that rhs is a reference to.
// We solve this problem by using cast operator dynamic_cast to downcast rhs to a
// ChoiceQuesion const&. If the downcast fails, the runtime will throw an
// exception of type std::bad_cast.
// We trade this use of exceptions to avoid both partial and mixed assignments.
// NOTE: g++ is issuing warnings for this source file while no warnings are
// being issued by clang++ and cl.exe 

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
  virtual TrueFalseQuestion& operator=(Question const& rhs) override {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    const TrueFalseQuestion rhs_tf = dynamic_cast<TrueFalseQuestion const&>(rhs);
    Question::operator=(rhs); // call base class operator= function ...
    return *this;
  }
  virtual ~TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
};

// multiple-choice question type ...
class ChoiceQuestion : public Question {
public:
  ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; } 
  virtual ChoiceQuestion& operator=(Question const& rhs) override {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    // make sure rhs is really a ChoiceQuestion
    const ChoiceQuestion rhs_cq = dynamic_cast<ChoiceQuestion const&>(rhs);
    // proceed with normal assignment of ChoiceQuestion to ChoiceQuestion
    Question::operator=(rhs); // call base class operator= function ...
    choices = rhs_cq.choices;
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

  // check for partial-assignments ...
  Question *pq1 = &cq1, *pq2 = &cq2;

  // now since all operator= in the inheritance hierarchy are virtual,
  // CheckQuestion's operator= is invoked. Using dynamic_cast, we downcast
  // the reference to Question to a reference to CheckQuestion to complete
  // the assignments between CheckQuestion objects ... 
  *pq1 = *pq2;
  pq1->display();
  pq2->display();
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

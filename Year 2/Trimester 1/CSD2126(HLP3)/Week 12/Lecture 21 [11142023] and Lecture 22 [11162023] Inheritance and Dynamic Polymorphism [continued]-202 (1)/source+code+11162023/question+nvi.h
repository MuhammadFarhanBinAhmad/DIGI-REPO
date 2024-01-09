// HLP3: question+nvi.h
// 11/05/2023
// Illustrates a hierarchy of question types that inherit from the
// abstract base class IQuestion [previously discussed in question.h]
// plus the Non-Virtual Idiom (NVI) and the Template Method Pattern.
#ifndef _QUESTION_HPP_
#define _QUESTION_HPP_

#include <iostream>
#include <string>
#include <vector>

// Abstract base class that specifies the interface for all question types.
// As a rule of thumb, ABCs should have no state. This make implementation
// of copy functions simpler. However, we make an exception to avoid having
// to add the text and answer data members to every class in the hierarchy.
// To avoid partial and mixed-type assignments, the copy functions are protected.
// Since clients cannot instantiate objects of type ABC, the ctors and dtor
// protected.
class IQuestion {
protected:
  IQuestion(std::string const& t, std::string const& a) : text{t}, answer{a} {}
  IQuestion(IQuestion const& rhs) : text{rhs.text}, answer{rhs.answer} {}
  IQuestion& operator=(IQuestion const& rhs) { text = rhs.text; answer = rhs.answer; return *this; }
// we're now using NVI because display() which was previously public has now
// become a private [protected here since derived classes will call the base class function]
  virtual std::ostream& display(std::ostream& os) const = 0;
public:
// we're applying the template method pattern by implementing the whole process of
// asking questions and checking answers in a non-virtual function called ask().
// This function is customized by derived classes thro' the private virtual function
// display().
  void ask(std::ostream& os) { // Template Method Pattern
    display(os);
    os << "Your answer: ";
    std::string response;
    getline(std::cin, response);
    os << (check_answer(response) ? "Correct\n" : "Wrong\n");
  }
  void set_text(std::string const& t) { text = t; }
  void set_answer(std::string const& a) { answer = a; }
  bool check_answer(std::string const& s) const { return s == answer; }
  virtual IQuestion* clone() const = 0;
  virtual ~IQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
protected:
  std::string text;
  std::string answer;
};

std::ostream& IQuestion::display(std::ostream& os) const { return os << text << '\n'; }

class ShortAnswerQuestion : public IQuestion {
public:
  ShortAnswerQuestion(std::string const& t, std::string const& a) : IQuestion(t,a) {}
  ShortAnswerQuestion(ShortAnswerQuestion const& rhs) : IQuestion(rhs) {}
  ~ShortAnswerQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ShortAnswerQuestion& operator=(ShortAnswerQuestion const& rhs) {
    IQuestion::operator=(rhs);
    return *this;
  }
  virtual IQuestion* clone() const override { return new ShortAnswerQuestion{*this}; }
private:
  virtual std::ostream& display(std::ostream& os) const override { return IQuestion::display(os); }
};

class TrueFalseQuestion : public IQuestion {
public:
  TrueFalseQuestion(std::string const& t, std::string const& a) : IQuestion(t,a) {}
  TrueFalseQuestion(TrueFalseQuestion const& rhs) : IQuestion(rhs) {}
  ~TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  TrueFalseQuestion& operator=(TrueFalseQuestion const& rhs) {
    IQuestion::operator=(rhs);
    return *this;
  }
  virtual IQuestion* clone() const override { return new TrueFalseQuestion{*this}; }
private:
  virtual std::ostream& display(std::ostream& os) const override { return IQuestion::display(os); }
};

class ChoiceQuestion : public IQuestion {
  std::vector<std::string> choices;
public:
  ChoiceQuestion(std::string const& t, std::string const& a, std::vector<std::string> const& c)
                 : IQuestion(t, a), choices{c} {}
  ChoiceQuestion(ChoiceQuestion const& rhs) : IQuestion(rhs), choices{rhs.choices} {}
  ~ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ChoiceQuestion& operator=(ChoiceQuestion const& rhs) {
    IQuestion::operator=(rhs);
    choices = rhs.choices;
    return *this;
  }
  virtual IQuestion* clone() const override { return new ChoiceQuestion{*this}; }
private:
  virtual std::ostream& display(std::ostream& os) const override { 
    IQuestion::display(os);
    std::vector<std::string>::size_type i{};
    for (std::string const& x : choices) {
      os << ++i << ": " << x << '\n';
    }
    return os;
  }
};

#endif

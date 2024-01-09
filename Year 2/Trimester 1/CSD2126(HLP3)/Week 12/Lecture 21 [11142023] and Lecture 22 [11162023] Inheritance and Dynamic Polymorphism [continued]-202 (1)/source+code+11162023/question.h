// HLP3: question.h
// 11/05/2023
// Illustrates a hierarchy of question types that inherit from the
// abstract base class IQuestion.
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
  IQuestion() = default;
  IQuestion(IQuestion const& rhs) = default;
  IQuestion& operator=(IQuestion const& rhs) = default;
public:
  virtual ~IQuestion() = 0;
  virtual void set_text(std::string const&) = 0;
  virtual void set_answer(std::string const&) = 0; 
  virtual bool check_answer(std::string const&) const = 0;
  virtual std::ostream& display(std::ostream& os) const = 0;
  virtual IQuestion* clone() const = 0;
};
IQuestion::~IQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

class ShortAnswerQuestion : public IQuestion {
public:
  ShortAnswerQuestion(std::string const& t, std::string const& a) : text{t}, answer{a} {}
  ShortAnswerQuestion(ShortAnswerQuestion const& rhs) : text(rhs.text), answer{rhs.answer} {}
  ~ShortAnswerQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ShortAnswerQuestion& operator=(ShortAnswerQuestion const& rhs) {
    text = rhs.text; answer = rhs.answer;
    return *this;
  }
  void set_text(std::string const& t) override { text = t; }
  void set_answer(std::string const& a) override { answer = a; }
  bool check_answer(std::string const& s) const override { return s == answer; }
  virtual std::ostream& display(std::ostream& os) const override { return os << text << '\n'; }
  virtual IQuestion* clone() const override { return new ShortAnswerQuestion{*this}; }
private:
  std::string text, answer;
};

class TrueFalseQuestion : public IQuestion {
public:
  TrueFalseQuestion(std::string const& t, std::string const& a) : text{t}, answer{a} {}
  TrueFalseQuestion(TrueFalseQuestion const& rhs) : text{rhs.text}, answer{rhs.answer} {}
  ~TrueFalseQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  TrueFalseQuestion& operator=(TrueFalseQuestion const& rhs) {
    text = rhs.text; answer = rhs.answer;
    return *this;
  }
  void set_text(std::string const& t) override { text = t; }
  void set_answer(std::string const& a) override { answer = a; }
  bool check_answer(std::string const& s) const override { return s == answer; }
  virtual std::ostream& display(std::ostream& os) const override { return os << text << '\n'; }
  virtual IQuestion* clone() const override { return new TrueFalseQuestion{*this}; }
private:
  std::string text, answer;
};

class ChoiceQuestion : public IQuestion {
  std::string text, answer;
  std::vector<std::string> choices;
public:
  ChoiceQuestion(std::string const& t, std::string const& a, std::vector<std::string> const& c)
                 : text{t}, answer{a}, choices{c} {}
  ChoiceQuestion(ChoiceQuestion const& rhs) : text{rhs.text}, answer{rhs.answer}, choices{rhs.choices} {}
  ~ChoiceQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ChoiceQuestion& operator=(ChoiceQuestion const& rhs) {
    text = rhs.text; answer = rhs.answer;
    choices = rhs.choices;
    return *this;
  }
  void set_text(std::string const& t) override { text = t; }
  void set_answer(std::string const& a) override { answer = a; }
  bool check_answer(std::string const& s) const override { return s == answer; }
  virtual std::ostream& display(std::ostream& os) const override { 
    os << text << '\n';
    std::vector<std::string>::size_type i{};
    for (std::string const& x : choices) {
      os << ++i << ": " << x << '\n';
    }
    return os;
  }
  virtual IQuestion* clone() const override { return new ChoiceQuestion{*this}; }
};

#endif

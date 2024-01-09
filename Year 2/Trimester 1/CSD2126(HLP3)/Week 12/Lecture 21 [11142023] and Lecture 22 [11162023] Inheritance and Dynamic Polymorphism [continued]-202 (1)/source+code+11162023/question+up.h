// HLP3: question+up.h
// 11/05/2023
// Illustrates the use of std::unique_ptr<> to encapsulate pointers to base class IQuestion
#ifndef _QUESTION_HPP_
#define _QUESTION_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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
public:
  void set_text(std::string const& t) { text = t; }
  void set_answer(std::string const& a) { answer = a; }
  bool check_answer(std::string const& s) const { return s == answer; }
  virtual std::ostream& display(std::ostream& os) const = 0;
  virtual std::unique_ptr<IQuestion> clone() const = 0;
  virtual ~IQuestion() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
private:
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
  virtual std::ostream& display(std::ostream& os) const override { return IQuestion::display(os); }
  virtual std::unique_ptr<IQuestion> clone() const override { 
    return std::make_unique<ShortAnswerQuestion>(*this); }
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
  virtual std::ostream& display(std::ostream& os) const override { return IQuestion::display(os); }
  virtual std::unique_ptr<IQuestion> clone() const override { 
    return std::make_unique<TrueFalseQuestion>(*this);
  }
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
  virtual std::ostream& display(std::ostream& os) const override { 
    IQuestion::display(os);
    std::vector<std::string>::size_type i{};
    for (std::string const& x : choices) {
      os << ++i << ": " << x << '\n';
    }
    return os;
  }
  virtual std::unique_ptr<IQuestion> clone() const override { 
    return std::make_unique<ChoiceQuestion>(*this); }
};

#endif

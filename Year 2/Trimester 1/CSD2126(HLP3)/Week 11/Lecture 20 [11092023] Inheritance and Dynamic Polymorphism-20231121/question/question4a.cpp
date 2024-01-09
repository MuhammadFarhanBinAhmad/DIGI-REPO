// HLP3: question4.cpp
// 11/09/2023
// Using pointers, we're now able to store the different classes in a
// class hierarchy in a container.
// However, we want to work with objects whose type and behavior can vary at run-time.
// This variation of behavior is achieved with virtual functions.
// When you invoke a virtual function on an object, the C++ run-time system determines
// which actual member function to call, depending on the class to which the
// object belongs.

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
/*
The keyword virtual tells the compiler to use the run-time type of the
object that the pointer is pointing to [and not its compile-time type!!!].
The reserved word virtual must be used in the base class. All functions with
the same name and parameter variable types in derived classes are then
automatically virtual.
*/
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

/*
The base class Question has a virtual function called display(). This derived
class inherits this virtual function from base class Question. However, this
derived class must provide its own definition of display() [because in addition
to the question text, this class must also display the multiple choices].
In this case, we say that the derived class needs to override the definition it
inherits from the base class by providing its own definition.
The base class defines as virtual those functions it expects its derived classes
to override. When we call a virtual function thro' a pointer or reference, the
call will be dynamically bound. If the base class pointer is pointing to a
base class object, the base class' display() is invoked. If the base class
pointer is pointing to a derived class object, the overriding derived class'
display() is invoked.

Suppose the base class has a non-virtual function foo:
class Question {
public:
  ...
  void foo();
};

If the derived class defines its own non-virtual function foo():
class ChoiceQuestion : public Question {
public:
  ...
  void foo(); 
};

then, we say that ChoiceQuestion::foo() hides Question::foo()!!!
The term overriding arises only in the context of virtual functions while
the term hiding arises in the context of non-virtual functions.
*/
  virtual void display() const; // since the declaration of this function matches
                                // the declaration of Question::display, the keyword
                                // virtual in this declaration is redundant.
                                // However, it is a good idea to include the keyword
                                // because it makes the code more literate.
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

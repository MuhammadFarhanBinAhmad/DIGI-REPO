// HLP3: question0.cpp
// 11/09/2023
// A quiz consists of questions of many types such as true/false, multiple-choice,
// short answer, fill in the blank; choice [single or multiple]; numeric [where
// approximate answer is ok, e.g., 1.33 is ok for 4/3]; free response; and so on.
// Although there are many types of questions, every question must contain the
// problem text, the correct answer, the ability to display the question, and
// the ability to check the answer provided by the user.
// These common features are encapsulated in type Question ...

#include <iostream>
#include <iomanip>
#include <string>

// basic [short answer] question ...
class Question {
public:
  Question() = default;
  void set_text(std::string const& question_text) { text = question_text; }
  void set_answer(std::string const& correct_response) { answer = correct_response; }
  bool check_answer(std::string const& response) const { return response == answer; }
  void display() const { std::cout << text << '\n'; }
private:
  std::string text;   // question ...
  std::string answer; // correct answer ...
};

int main() {
  // set a basic question ...
  Question q1;
  q1.set_text("Who was the inventor of C++?");
  q1.set_answer("Bjarne Stroustrup");

  // ask a basic question ...
  q1.display();
  std::cout << "Your answer: ";
  std::string response;
  getline(std::cin, response);
  std::cout << (q1.check_answer(response) ? "Correct answer\n" : "Wrong answer\n");
}

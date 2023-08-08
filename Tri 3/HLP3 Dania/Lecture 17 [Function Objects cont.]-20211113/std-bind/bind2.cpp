// CSD2125: 11/11
// Another example of using std::bind to handle partial function implementation.
// Here, we're using std::bind with standard algorithms and containers
// containing pointer
#include <iostream>
#include <functional>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>

class Person {
private:
  std::string name;
public:
  Person(std::string const& n) : name{n} {}
  void print() const { std::cout << name << "\n"; }
  void print2(std::string const& prefix) const { std::cout << prefix << " " << name << "\n"; }
};

int main() {
  // container of pointers with exclusive ownership ...
  std::vector<std::unique_ptr<Person>> up;
  up.push_back(std::make_unique<Person>(Person("tic")));
  up.push_back(std::make_unique<Person>(Person("tac")));
  up.push_back(std::make_unique<Person>(Person("toe")));
  
  // use std::bind to invoke Person::print and Person::print2 for
  // every element of container of unique_ptrs
  std::for_each(up.begin(), up.end(), std::bind(&Person::print, std::placeholders::_1));
  std::for_each(up.begin(), up.end(),
               std::bind(&Person::print2, std::placeholders::_1, "Unique Person"));
  
  // do same using lambda expression
  std::for_each(up.begin(), up.end(), [](std::unique_ptr<Person> const& p) { p->print(); });
  std::for_each(up.begin(), up.end(),
     [](std::unique_ptr<Person> const& p) { p->print2("Unique Lambda Person"); });
  std::string per("Unique Lambda Capture Person");
  std::for_each(up.begin(), up.end(), [&per](std::unique_ptr<Person> const& p) { p->print2(per);}); 
  
  // container of pointers with shared ownership ...
  std::vector<std::shared_ptr<Person>> sp;
  sp.push_back(std::make_shared<Person>(Person("tic")));
  sp.push_back(std::make_shared<Person>(Person("tac")));
  sp.push_back(std::make_shared<Person>(Person("toc")));
  
  // use std::bind to invoke Person::print and Person::print2 for
  // every element of container of shared_ptrs
  std::for_each(sp.begin(), sp.end(), std::bind(&Person::print, std::placeholders::_1));
  std::for_each(sp.begin(), sp.end(), 
               std::bind(&Person::print2, std::placeholders::_1, "Shared Person"));
  
  // repeat with raw pointers ...
  std::vector<Person*> rp;
  rp.push_back(new Person {"tic"});
  rp.push_back(new Person {"tac"});
  rp.push_back(new Person {"toe"});
  // print using bind
  std::for_each(rp.begin(), rp.end(), std::bind(&Person::print, std::placeholders::_1));
  std::for_each(rp.begin(), rp.end(), 
               std::bind(&Person::print2, std::placeholders::_1, "Raw Person"));
  // release memory using delete
  std::for_each(rp.rbegin(), rp.rend(), [](Person *p) {delete p;});
}

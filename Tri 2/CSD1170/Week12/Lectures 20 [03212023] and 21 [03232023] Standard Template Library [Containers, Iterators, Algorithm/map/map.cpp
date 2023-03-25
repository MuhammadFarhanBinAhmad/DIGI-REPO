// HLP2 02/2020
// Maps and multimaps are containers that manage key/value pairs as elements.
// These containers sort their elements automatically, according to a certain
// sorting criterion that is used for the key. The difference between the
// two is that multimaps allow duplicates, whereas maps do not.
// For class templates map<K,V> and multimap<K,V>, the first template type
// parameter K is the type of the element's key, and the second template
// parameter V is the type of the element's associated value.
// The elements of a map or a multimap may have any types K and V that meet
// the following two requirements:
// 1) Both key and value must be copyable 
// 2) The key must be comparable with the sorting criterion.
//
// A map supports many different operations of which four are key:
// 1) Inserting a new key/value pair
// 2) Checking whether a particular key exists
// 3) Querying which value is associated with a given key
// 4) Removing an existing key/value pair

#include <iostream>
#include <string>
#include <map>

template <typename Container>
void print_map(Container const& coll, std::string const& prefix, std::string const& postfix="\n") {
  std::cout << prefix;
  for (typename Container::const_reference x : coll) {
    std::cout << x.first << " -> " << x.second << "\n";
  }
  std::cout << postfix;
}

// function object to determine if left parameter is greater than right parameter ...
template <typename T>
struct greater_than {
  bool operator()(T const& lhs, T const& rhs) const { return lhs > rhs; }
};

int main() {
  // If we want to construct a map<K,V> with an initializer list, each element
  // of the initializer list supplied as argument to the map<K,V> ctor must
  // be of type: pair<const K,V>
  using PSS = std::pair<const std::string,size_t>;
  std::initializer_list<PSS> pss{
    std::make_pair("John", 425'558'1111),
    std::make_pair("James", 425'558'1112)
  };
  // ctor using an initializer_list<value_type> ...
  std::map<std::string, size_t> phone_book{pss};
  print_map(phone_book, "phone_book:\n");

  // insert a new key/value pair using operator[] ...
  phone_book["Tom"] = 202'456'1111;
  phone_book["Dick"] = 202'456'2222;
  phone_book["Harry"] = 202'456'0011;
  phone_book["Clint"] = 202'456'0000;

  // Add more names to the phone book using insert():
  // Unlike op[], insert() doesn't do anything if key exists. To mitigate this,
  // insert() returns a value of type pair<iterator,bool>.
  // The bool value in the pair indicates whether the insert operation succeeded.
  // A result of true means that the key/value pair was added, while a result of
  // false means that the key already existed.
  // The iterator returned by insert() points either to the newly added pair
  // or to the existing pair ...
  std::pair<std::map<std::string,size_t>::iterator,bool> result =
          phone_book.insert(std::make_pair("Mary", 425'558'2222));
  if (result.second) {
    std::cout << "Mary's phone number " << result.first->second << " was added!!!\n";
  } else {
    std::cout << "Mary's phone number " << result.first->second << " previously existed!!!\n";
  }
  // try again to insert Mary's number ...
  result = phone_book.insert(std::make_pair("Mary", 425'558'2222));
  if (result.second) {
    std::cout << "Mary's phone number " << result.first->second << " was added!!!\n";
  } else {
    std::cout << "Mary's phone number " << result.first->second << " previously existed!!!\n";
  }
  print_map(phone_book, "\nphone_book:\n");

  // query Tom's phone number ...
  std::cout << "Tom's phone number: " << phone_book["Tom"] << "\n";

  // amending John's phone number:
  std::cout << "John's old phone number: " << phone_book["John"] << "\n";
  phone_book["John"] = 425'123'4567;
  std::cout << "John's new phone number: " << phone_book["John"] << "\n";

  // careful!!! if "Paul" doesn't exist, operator[] will create a
  // new element with key=string("Paul") and value equivalent to 0 ...
  std::cout << "New friend Paul's phone number: " << phone_book["Paul"] << "\n";
  // assign a new phone number for Paul
  phone_book["Paul"] = 425'558'3333;

  print_map(phone_book, "\nphone_book:\n");

  // check whether a key exists using find()
  std::string name{"Tom"};
  std::map<std::string, size_t>::iterator it = phone_book.find(name);
  if (it == std::end(phone_book)) {
    std::cout << name << " doesn't exist in phone book!!!\n";
  } else {
    std::cout << it->first << "'s phone number is: " << it->second << "\n";
  }

  // name is no longer a friend, so we erase that name from phone book:
  size_t erase_val = phone_book.erase(name);
  std::cout << name << " is " << (erase_val ? "" : "not ") << "erased from phone book!!!\n";

  print_map(phone_book, "\nphone_book:\n");

  // make a copy of map with different sorting criterion;
  std::map<std::string,size_t, greater_than<std::string>> 
                      rev_phone_book(std::begin(phone_book), std::end(phone_book));
  print_map(phone_book, "\nrev_phone_book:\n");
}
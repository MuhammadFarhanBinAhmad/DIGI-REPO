// HLP2: string.h [pghali@digipen.edu]
#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstddef>  // for size_t
#include <iostream> // for std::ostream
#include <initializer_list>
#include <string>

namespace hlp2 {

class String {
public:
  using value_type             = char;
  using size_type              = size_t;
  using reference              = value_type&;
  using const_reference        = const value_type&;
  using pointer                = value_type*;
  using const_pointer          = const value_type*;
  using iterator               = pointer;
  using const_iterator         = const_pointer;
  using reverse_iterator       = pointer;
  using const_reverse_iterator = const_pointer;

public:
  String();
  String(const_pointer);
  String(String const&);
  String(std::initializer_list<char>);
  ~String();

  String& operator=(String const&);
  String& operator=(const_pointer);
  String& operator=(std::initializer_list<char>);
  String& operator+=(String const&);
  String& operator+=(const_pointer);
  String& operator+=(std::initializer_list<char>);

  reference at(size_type idx) {
    if (idx >= len) {
      throw (idx);
    }
    return data[idx];
  }
  reference at(size_type idx) const {
    if (idx >= len) {
      std::string str = std::to_string(idx) + " is a bad value!!!!";
      throw (str);
    }
  }

  reference operator[](size_type);
  const_reference operator[](size_type) const;

  size_type size() const;
  bool empty() const;
  const_pointer c_str() const;
  int compare(String const& rhs) const;
  void swap(String&);

  iterator               begin();
  const_iterator         begin() const;
  iterator               end();
  const_iterator         end() const;
  const_iterator         cbegin() const;
  const_iterator         cend() const;

  static size_type       get_count();
private:
  size_type len;
  pointer   data;
  static size_type counter;
};

String operator+(String const&, String const&);
String operator+(String const&, String::const_pointer);
String operator+(String::const_pointer, String const&);

bool operator==(String const&, String const&);
bool operator!=(String const&, String const&);
bool operator< (String const&, String const&);
bool operator<=(String const&, String const&);
bool operator> (String const&, String const&);
bool operator>=(String const&, String const&);

std::ostream& operator<<(std::ostream&, String const&);
std::istream& operator>>(std::istream&, String&);

} // endif namespace hlp2

#endif

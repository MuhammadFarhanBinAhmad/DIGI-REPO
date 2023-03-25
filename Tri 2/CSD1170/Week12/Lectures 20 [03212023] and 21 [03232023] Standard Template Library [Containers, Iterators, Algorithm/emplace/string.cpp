// HLP2: string.cpp [pghali@digipen.edu]
#include "string.h"
#include <cstring>
#include <iostream>
#include <algorithm>

namespace hlp2 {

String::size_type String::counter {0};

String::String() : len{0}, data{new char [len+1]} {
#ifdef DEBUG
  std::cout << "String::String()\n";
#endif
  data[0] = '\0';
  ++counter;
}

String::String(String::const_pointer rhs)
: len{std::strlen(rhs)}, data{new char [len+1]} {
#ifdef DEBUG
  std::cout << "String::String(char const*): " << rhs << "\n";
#endif
  std::strcpy(data, rhs);
  ++counter;
}

String::String(String const& rhs)
: len{rhs.len}, data{new char [len+1]} {
#ifdef DEBUG
  std::cout << "String::String(String const&): " << rhs.data << "\n";
#endif
  std::strcpy(data, rhs.data);
  ++counter;
}

String::String(std::initializer_list<char> lst) 
: len{lst.size()}, data{new char [len+1]} {
  char *tmpptr {data};
  for (char const *p {lst.begin()}; p != lst.end(); ++p) {
    *tmpptr++ = *p;
  }
  *tmpptr = '\0';
  ++counter;
#ifdef DEBUG
  std::cout << "String::String(initializer_list<char>): " << data << "\n";
#endif
}

String::~String() {
#ifdef DEBUG
  std::cout << "String::~String(): " << data << "\n";
#endif
  delete [] data;
  --counter;
}

String& String::operator=(String const& rhs) {
  String tmp{rhs};
  swap(tmp);
  return *this;
}

String& String::operator=(String::const_pointer rhs) {
  String tmp{rhs};
  swap(tmp);
  return *this;
}

String& String::operator=(std::initializer_list<char> lst) {
  String tmp{lst};
  swap(tmp);
  return *this;
}

String& String::operator+=(String const& rhs) {
  size_type tmp_len { len + rhs.len };
  pointer   tmp_data { new value_type [tmp_len + 1]};
  std::strcpy(tmp_data, data);
  std::strcat(tmp_data, rhs.data);

  len = tmp_len;
  delete [] data; data = tmp_data;

  return *this;
}

String& String::operator+=(String::const_pointer rhs) {
  size_type tmp_len { len + std::strlen(rhs)};
  pointer   tmp_data { new value_type [tmp_len + 1]};
  std::strcpy(tmp_data, data);
  std::strcat(tmp_data, rhs);

  len = tmp_len;
  delete [] data; data = tmp_data;

  return *this;
}

String& String::operator+=(std::initializer_list<char> lst) {
  size_type tmp_len { len + lst.size() };
  pointer   tmp_data { new value_type [tmp_len + 1] };
  std::strcpy(tmp_data, data);
  char *tmp_data2 {tmp_data + len};
  for (char const *p = lst.begin(); p != lst.end(); ++p) {
    *tmp_data2++ = *p;
  }
  *tmp_data2 = '\0';

  len = tmp_len;
  delete [] data; data = tmp_data;

  return *this;
}

String::reference String::operator[](String::size_type index) {
  //return data[index];
  return const_cast<reference>((static_cast<String const&>(*this))[index]);
}

String::const_reference String::operator[](String::size_type index) const {
  return data[index];
}

String::size_type String::size() const {
  return len;
}

bool String::empty() const {
  return len == 0;
}

String::const_pointer String::c_str() const {
  return data;
}

int String::compare(String const& rhs) const {
  return std::strcmp(data, rhs.data);
}

void String::swap(String& rhs) {
  std::swap(len, rhs.len);
  std::swap(data, rhs.data);
}

String::iterator String::begin() {
  return data;
}
String::const_iterator String::begin() const {
  return data;
}
String::iterator String::end() {
  return data+len;
}
String::const_iterator String::end() const {
  return data+len;
}
String::const_iterator String::cbegin() const {
  return data;
}
String::const_iterator String::cend() const {
  return data+len;
}

String operator+(String const& lhs, String const& rhs) {
  String tmp {lhs};
  tmp += rhs;
  return tmp;
}

String operator+(String const& lhs, String::const_pointer rhs) {
  String tmp {lhs};
  tmp += rhs;
  return tmp;
}

String operator+(String::const_pointer lhs, String const& rhs) {
  String tmp {lhs};
  tmp += rhs;
  return tmp;
}

bool operator==(String const& lhs, String const& rhs) {
  return lhs.compare(rhs)==0 ? true : false;
}
bool operator!=(String const& lhs, String const& rhs) {
  return !(lhs == rhs);
}
bool operator< (String const& lhs, String const& rhs) {
  return lhs.compare(rhs) < 0 ? true : false;
}
bool operator<=(String const& lhs, String const& rhs) {
 return lhs.compare(rhs) <= 0 ? true : false;
}
bool operator> (String const& lhs, String const& rhs) {
  return lhs.compare(rhs) > 0 ? true : false;
}
bool operator>=(String const& lhs, String const& rhs) {
 return lhs.compare(rhs) >= 0 ? true : false;
}

std::ostream& operator<<(std::ostream& os, String const& rhs) {
  os << rhs.c_str();
  return os;
}

std::istream& operator>>(std::istream& is, String& rhs) {
  int const max_buff_size {1024};
  String::value_type buffer[max_buff_size];
  is.width(max_buff_size-1);
  is >> buffer;
  rhs = buffer;
  return is;
}

String::size_type String::get_count() {
  return String::counter;
}

} // end namespace hlp2
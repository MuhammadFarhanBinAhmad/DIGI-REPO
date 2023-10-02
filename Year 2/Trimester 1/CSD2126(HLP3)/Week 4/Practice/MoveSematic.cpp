#include <iostream>
#include <string>
#include <memory>
class MyString {
public:
    // Constructor
    MyString(const std::string& str) : data(new std::string(str)) {
        std::cout << "Constructor: " << *data << std::endl;
    }

    // Move Constructor
    MyString(MyString&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move Constructor: " << *data << std::endl;
    }

    // Move Assignment Operator
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "Move Assignment: " << *data << std::endl;
        }
        return *this;
    }

    // Destructor
    ~MyString() {
        if (data) {
            std::cout << "Destructor: " << *data << std::endl;
        }
    }

private:
    std::unique_ptr<std::string> data;
};

int main() {
    MyString str1("Hello, World!"); // Constructor

    MyString str2(std::move(str1)); // Move Constructor
    // str1 is now in a valid but unspecified state

    MyString str3("Goodbye, World!"); // Constructor

    str1 = std::move(str3); // Move Assignment
    // str3 is now in a valid but unspecified state

    return 0;
}

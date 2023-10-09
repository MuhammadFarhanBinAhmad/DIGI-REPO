// Move_Semantics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

class MyString
{
public:

    MyString() = default;
    MyString(const char* string)
    {
        std::cout << "Created\n";
        m_Size = strlen(string);
        m_Data = new char[m_Size];
        memcpy(m_Data, string, m_Size);
    }

    MyString(const MyString& other)
    {
        std::cout << "Copied\n";
        m_Size = other.m_Size;
        m_Data = new char[m_Size];
        memcpy(m_Data, other.m_Data, m_Size);
    }

    MyString(MyString&& other) noexcept
    {
        std::cout << "Move\n";
        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Data = nullptr;
        other.m_Size = 0;
    }

    MyString& operator=(MyString&& other) noexcept
    {
        if (this == &other)
        {
            std::cout << "Same Object\n";
            return *this;
        }

        std::cout << "Move Assignment\n";

        delete[] m_Data;

        m_Size = other.m_Size;
        m_Data = other.m_Data;

        other.m_Data = nullptr;
        other.m_Size = 0;

        return *this;
    }

    ~MyString()
    {
        std::cout << "Destroyed\n";
        delete m_Data;
    }

    void Print()
    {
        for (uint32_t i = 0; i < m_Size; i++)
        {
            std::cout << m_Data[i];
        }
        std::cout << '\n';
    }
private:
    char* m_Data;
    uint32_t m_Size;
};

class Entity
{
public:
    Entity(const MyString& name):m_name(name)
    {}
    Entity(MyString&& name) : m_name(std::move(name)) 
    {}
    void PrintName()
    {
        m_name.Print();
    }
private:
    MyString m_name;
};

int main()
{
    Entity entity("Testcase");//Call base contructor first then copy constructor. Making 2 copy. Want to avoid that

    entity.PrintName();

    MyString string = "Hello";
    MyString dest = std::move(string);//will use move constructor not move assignment

    //MOVE ASSIGNMENT
    MyString fruit;
    MyString apple("Apple");


    std::cout << "fruit: ";
    fruit.Print();
    std::cout << "apple: ";
    apple.Print();

    fruit = std::move(apple);//will call move assignment

    std::cout << "fruit: ";
    fruit.Print();
    std::cout << "apple: ";
    apple.Print();

}
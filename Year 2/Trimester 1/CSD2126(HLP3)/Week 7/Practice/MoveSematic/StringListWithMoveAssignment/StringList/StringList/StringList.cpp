// StringList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

class MyString
{
public:
	MyString() = default;
	MyString(const char* name, const char* mod, float GPA)
	{
		std::cout << "Created\n";
		int name_size = strlen(name);
		int module_size = strlen(mod);
		m_GPA = GPA;

		m_name = new char [name_size+1];
		m_module = new char[module_size+1];

		memcpy(m_name, name, name_size);
		m_name[name_size] = '\0';
		memcpy(m_module, mod, module_size);
		m_module[module_size] = '\0';
	}
	~MyString()
	{
		std::cout << "Destroyed\n";
		delete[] m_name;
		delete[] m_module;
	}
	MyString(const MyString& other)
	{
		std::cout << "Copied\n";
		int name_size = strlen(other.m_name);
		int module_size = strlen(other.m_module);
		m_GPA = other.m_GPA;

		m_name = new char[name_size];
		m_module = new char[module_size];

		memcpy(m_name, other.m_name, name_size);
		memcpy(m_module, other.m_module, module_size);
	}

	MyString(MyString&& other) noexcept
	{
		std::cout << "Move\n";
		this->m_name = other.m_name;
		this->m_module = other.m_module;
		this->m_GPA = other.m_GPA;

		other.m_name = nullptr;
		other.m_module = nullptr;
		other.m_GPA = 0;
	}

	MyString& operator=(MyString&& other) noexcept
	{
		std::cout << "Move Assignment\n";
		if (this == &other)
		{
			return *this;
		}

		//need delete to avoid memleak
		delete[] m_name;
		delete[] m_module;

		this->m_name = other.m_name;
		this->m_module = other.m_module;
		this->m_GPA = other.m_GPA;

		other.m_name = nullptr;
		other.m_module = nullptr;
		other.m_GPA = 0;

		return *this;
	}

	void Print()
	{
		std::cout << "Student name: ";
		if (m_name != nullptr)
		{
			int name_size = strlen(m_name);
			for (int i = 0; i < name_size; i++)
			{
				std::cout << m_name[i];
			}
		}
		std::cout << '\n';

		std::cout << "Student module: ";
		if (m_module != nullptr)
		{
			int module_size = strlen(m_module);

			for (int i = 0; i < module_size; i++)
			{
				std::cout << m_module[i];
			}
		}
		std::cout << '\n';

		std::cout << "GPA: " << m_GPA << '\n';

	}

	void Swap(MyString& lhs, MyString& rhs)
	{
		std::cout << "Move semantic swap\n";
		MyString temp = std::move(lhs);
		lhs = std::move(rhs);
		rhs = std::move(temp);
	}

private:
	char* m_name;
	char* m_module;
	float m_GPA;
};

class Student
{
public:
	Student(const MyString& student):m_Student(student)
	{}
	Student(MyString&& student) :m_Student(std::move(student))
	{}

	void PrintStudent()
	{
		m_Student.Print();
	}
private:
	MyString m_Student;
};

int main()
{
	MyString Stud_01("James", "CSD2012", 2.4);
	MyString Stud_02("May", "CSD2022", 3.6);
	MyString Stud_03("Hammond", "CSD2023", 4.1);

	//BEFORE MOVE
	std::cout << "BEFORE MOVE ASSIGNMENT\n";
	std::cout << "Student 1:\n";
	Stud_01.Print();
	std::cout << "Student 2:\n";
	Stud_02.Print();
	std::cout << "Student 3:\n";
	Stud_03.Print();

	//Move assigment
	//Student 1 will "steal" student 2 content
	//Basically stud_02 stuff move to stud_01
	Stud_01 = std::move(Stud_02);

	//AFTER MOVE
	std::cout << "AFTER MOVE ASSIGNMENT\n";
	std::cout << "Student 1:\n";
	Stud_01.Print();
	std::cout << "Student 2:\n";
	Stud_02.Print();
	std::cout << "Student 3:\n";
	Stud_03.Print();

	//ADD NEW STUDENT
	MyString n_Student("Stig", "CSD6969", 5.0);
	Stud_02 = std::move(n_Student);

	std::cout << "Student 1: ";
	Stud_01.Print();
	std::cout << "Student 2: ";
	Stud_02.Print();
	std::cout << "Student 2: ";
	Stud_03.Print();


}


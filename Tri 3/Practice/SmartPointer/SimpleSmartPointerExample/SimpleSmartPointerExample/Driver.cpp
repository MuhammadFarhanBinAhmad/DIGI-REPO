
//class Person
//{
//public:
//	Person(const std::string name) : Name(name)
//	{
//		std::cout << "Person " << Name << " create\n";
//	}
//	~Person() {
//		std::cout << "Person " << Name << " destroyed\n";
//	}
//
//private:
//	std::string Name;
//};
//
//int main()
//{
//	std::shared_ptr<Person> smartptr1 = std::make_shared<Person>("Joe");
//	std::shared_ptr<Person> smartptr2 = smartptr1;
//
//	Person* personPtr1 = new Person("Nig");
//	Person* personPtr2 = personPtr1;
//
//	delete personPtr1;
//
//	//Accessing reference counting
//	std::cout << "smartptr1.use_count(): " << smartptr1.use_count() << '\n';
//	std::cout << "smartptr2.use_count(): " << smartptr2.use_count() << '\n';
//
//	return 0;
//}
// LibraryManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Library.h"
#include "User.h"

int main()
{
	std::ifstream BookList_File;

	BookList_File.open("BookList.txt");
	std::string BookList;
	std::string temp;

	std::vector<std::shared_ptr<Book>> Books_Vector;

	int line_Counter = 0;
	int total_Books = 1;

	if (!BookList_File)
	{
		std::cout << "File not found" << std::endl;
	}

	//Dynamically allocate memory for Book
	std::shared_ptr<Book> b = std::make_shared<Book>();

	Books_Vector.push_back(b);


	while (std::getline(BookList_File, temp))
	{
		switch (line_Counter)
		{
		case 0:
			Books_Vector[total_Books - 1]->SetTitle(temp);
			break;
		case 1:
			Books_Vector[total_Books - 1]->SetAurthor(temp);
			break;
		case 2:
			Books_Vector[total_Books - 1]->SetISBN(std::stoll(temp));
			break;
		}
		if (line_Counter == 2)
		{

			line_Counter = 0;
			total_Books++;
			std::shared_ptr<Book> b = std::make_shared<Book>();

			Books_Vector.push_back(b);
		}
		else
		{
			line_Counter++;
		}
	}
	std::vector<std::shared_ptr<Book>>::iterator bk_itr;

	for (bk_itr = Books_Vector.begin(); bk_itr < Books_Vector.end() -1; bk_itr++)
	{ 
		std::cout << (*bk_itr)->GetAurthor() << std::endl;
	}

	BookList_File.close();


	//// Delete dynamically allocated Book objects
	//for (Book* book : Books_Vector)
	//{
	//	delete book;
	//}

	// Clear the vector
	Books_Vector.clear();


#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

}

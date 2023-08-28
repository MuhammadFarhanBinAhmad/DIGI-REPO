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

	std::vector<Book*> Books_Vector;

	int line_Counter = 0;
	int total_Books = 1;

	if (!BookList_File)
	{
		std::cout << "File not found" << std::endl;
	}

	//Dynamically allocate memory for Book
	Book* b = new Book;


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
			Book* b = new Book;
			Books_Vector.push_back(b);
		}
		else
		{
			line_Counter++;
		}
	}

	for (Book *b: Books_Vector)
	{
		std::cout << b->GetAurthor() << '\n';
	}

	BookList_File.close();


	// Delete dynamically allocated Book objects
	for (Book* book : Books_Vector) 
	{
		delete book;
	}

	// Clear the vector
	Books_Vector.clear();

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

}

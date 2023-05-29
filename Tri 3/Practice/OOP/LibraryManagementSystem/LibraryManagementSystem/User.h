#pragma once

#include "Book.h"

#include <vector>

class User
{
public:
	void Display_BooksBorrowed();
private:
	std::vector<Book> Book_Borrowed;
	std::string Name;

};
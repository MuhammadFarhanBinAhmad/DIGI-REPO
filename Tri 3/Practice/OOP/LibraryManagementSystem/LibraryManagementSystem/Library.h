#pragma once
#include "Book.h"

#include <vector>

class Library
{
public:

	void DisplayAllBook();
	void DisplayBooks(int64_t ISBN);
	void SetBookLender(int64_t ISBN,std::string Lender);


private:
	std::vector<Book> list_Book;
};
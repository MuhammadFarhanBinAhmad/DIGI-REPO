#pragma once
#include "Book.h"
#include "Library.h"

#include <vector>

class Library
{
public:
	Library();
	~Library();

	void PrintAllBook();
	void GetBook();
	void SetBook();

private:
	std::vector<Book> list_Book;
};

Library::Library()
{
}

Library::~Library()
{
}
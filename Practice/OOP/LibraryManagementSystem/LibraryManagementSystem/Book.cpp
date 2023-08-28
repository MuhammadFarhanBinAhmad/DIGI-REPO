#include "Book.h"

void Book::SetTitle(std::string new_Title){ Title = new_Title; }
void Book::SetAurthor(std::string new_Author) { Aurthor = new_Author; }
void Book::SetLender(std::string new_Lender) { Lender = new_Lender; }
void Book::SetISBN(int64_t new_ISBN) { ISBN = new_ISBN; }
void Book::SetAvailability(bool new_Availability) { Availability = new_Availability; }

Book::Book() :
	Title{ "NULL" },
	Aurthor{ "NULL" },
	Lender{ "NULL" },
	ISBN{ 0000000000000 }
{}

Book::Book(const Book& copy_Book) :
	Title{ copy_Book.Title },
	Aurthor { copy_Book.Aurthor},
	Lender{copy_Book.Lender},
	ISBN{copy_Book.ISBN}
{

}

Book::~Book()
{
	//nothing much to do here unless something dynamically allocated is done here
}

Book& Book::operator=(const Book& copy_book)
{
	//SafeGuard
	if (this == &copy_book)
	{
		return *this;
	}

	Title = copy_book.Title;
	Aurthor = copy_book.Aurthor;
	Lender = copy_book.Lender;
	ISBN = copy_book.ISBN;

	return *this;
}

std::string Book::GetTitle() { return Title; }
std::string Book::GetAurthor() { return Aurthor; }
std::string Book::GetLender() { return Lender; }
int64_t Book::GetISBN() { return ISBN; }
bool Book::GetAvailability() { return Availability; }
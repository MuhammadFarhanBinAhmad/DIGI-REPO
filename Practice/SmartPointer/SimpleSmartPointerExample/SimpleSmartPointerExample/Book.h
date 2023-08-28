#pragma once
#include <string>
#include <iostream>

class Book
{
private:
	std::string Title;
	std::string Aurthor;
	std::string Lender;
	int64_t ISBN;
	bool Availability;

public:
	Book();
	Book(const Book& copy_Book);//copy constructor
	//Need set to const because want to copy. If not set to const, can cause unexpected behaviour
	~Book();

	Book& operator=(const Book& copy_book);//copy assignment


	void SetTitle(std::string new_Title);
	void SetAurthor(std::string new_Author);
	void SetLender(std::string new_Lender);
	void SetISBN(int64_t new_ISBN);
	void SetAvailability(bool new_Availability);

	std::string GetTitle();
	std::string GetAurthor();
	std::string GetLender();
	int64_t GetISBN();
	bool GetAvailability();
};

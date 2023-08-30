#include "uShell.h"
#include <iostream>

uShell::uShell(bool bFlag)
{

}

bool uShell::getInput(std::string& input) const
{
	std::string temp_str = input;
	if (temp_str.back() == '\r')
	{
		temp_str.pop_back();
		return true;
	}
	return false;
}


void uShell::printVerbose(std::string const& input)
{
	std::string temp_str = input;
	int pos = temp_str.find_first_of(' ');
	pos++;//go next char since it's start of a word
	while (temp_str[pos] != ' ')
	{
		std::cout << temp_str[pos];
		pos++;
	}
}

void uShell::tokenize(std::string const& input, TokenList& tokenList) const
{
	int pos = 0;
	bool is_space = true;

	std::string copy_str = input;
	std::string insert_str;

	//Check for end of string
	while (copy_str[pos] != '\0')
	{
		if (copy_str[pos] != ' ')
		{
			if (is_space)
			{
				is_space = false;
			}
			insert_str += copy_str[pos];
		}
		else
		{
			is_space = true;
			tokenList.push_back(insert_str);
			insert_str.clear();
		}
		pos++;
	}
	//Insert last word cause loop break before inserting last word
	tokenList.push_back(insert_str);
}


bool uShell::replaceVars(TokenList& tokenList) const
{

}


bool uShell::isValidVarname(char const* start, char const* end) const
{
	while (start != end)
	{
		if (!isalpha(*start) || !isdigit(*start))
		{
			return false;
		}
	}
	return true;
}

std::string uShell::mergeTokens(TokenList const& tokenList, unsigned startPos) const
{
	std::string Word;

	for (unsigned i = startPos; i < tokenList.size(); i++)
	{
		Word += tokenList[i];
		Word += ' ';
	}

	return Word;
}

void uShell::echo(TokenList const& tokenList)
{
	int i = 1;

	for (i; i < tokenList.size(); i++)
	{
		std::cout << tokenList[i] << ' ';
	}
}

void uShell::setVar(TokenList const& tokenList)
{

}

int uShell::run()
{

}

/*!************************************************************************
\file   uShell.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS
\date   09-09-2023

\brief 	Create a basic shell program
		called uShell. A shell program behaves typically in a similar fashion to a command prompt.
		Usually, it has the following capabilities:
		 Ignore comments statement
		 Perform internal commands
		 Run programs and launch processes
		 Setting of environment variables
		 Perform input/output redirection (To be done later)
		 Performing piping as a means of interprocess communications between processes (To
		be done in later)
**************************************************************************/
#include "uShell.h"
#include <iostream>
#include <functional>
#include <sstream>
using EchoFunction = void (*)(const std::string &);

/************************************************************************/
/*!
\brief
Creates the class object of uShell
\param bFlag
boolean value to decide whether to echo input
*/
/************************************************************************/
uShell::uShell(bool bFlag) : m_verbose(bFlag), m_exit(false), m_exitCode(0)
{
	// Function pointer for the internal command
	m_internalCmdList["echo"] = &uShell::echo;
	m_internalCmdList["setvar"] = &uShell::setVar;

	m_prompt = "uShell";
}
/************************************************************************/
/*!
\brief 
Get one line of input from std:: cin. Removes the trailing \r if any 
This function obtains a line from input stream and check whether the last character, is a
‘\r’, and remove it. This caters to file formats that has ‘\r’ with ‘\n’.
\param input
The input string to take the user input by reference
\return
return false if encountering the EOF
*/
/************************************************************************/
bool uShell::getInput(std::string &input) const
{
	std::string temp_str = input;

	if (input.empty())
	{
		return false;
	}
	if (temp_str.back() == '\r')
	{
		temp_str.erase(temp_str.end() - 1);
	}

	return true;
}
/************************************************************************/
/*!
\brief
Print the user input without printing the starting and the trailing spaces.
It finds the first last non-space positions and prints everything in between. Remember to
print the line end.
\param input
The input string
*/
/************************************************************************/
void uShell::printVerbose(std::string const &input)
{

	size_t first = input.find_first_not_of(" \t\n\r\f\v");
	size_t last = input.find_last_not_of(" \t\n\r\f\v");

	if (first != std::string::npos || last != std::string::npos)
	{
		std::cout << input.substr(first, last + 1) << std::endl;
	}
}
/************************************************************************/
/*!
\brief
Tokenize the input string into a list of strings which are separated by 
spaces.
It gets the string stream from the input and obtains each token item by item by pushing
the item to token list.
\param input
The input string given by the user
\param tokenList
Token list to fill up, passed by reference to add strings to it
*/
/************************************************************************/
void uShell::tokenize(std::string const &input, TokenList &tokenList) const // works
{
	std::string word;
	std::stringstream iss(input);

	while (iss >> word)
	{
		tokenList.push_back(word);
	}
}
/************************************************************************/
/*!
\brief
Search and replace from the map all variables in the token list with the value 
In this function it loop through all tokens in the token list. In each iteration, it checks each
token for comment. If there is comment sign, it removes all the following tokens (including
this) and terminates the loop. Otherwise, it detects if each token has a variable within.
Furthermore it checks if this token has ‘{’ following the ‘$’ sign. If not, it tries to find the
next ‘$’ sign. If there is a ‘{’, it then searches for the first instance of ‘}’ after ‘${’. If there
is no ‘}’ in the token, it just skips. However, if the ‘}’ is in the token, it continues to do
changing for the variable in the token string.
It checks if the variable name is valid by determining whether every character in between
is a proper character (using function isValidVarname()). If it is invalid, it abort the attempt
to change. Otherwise, it gets the string between ‘${’ and ‘}’ and check whether the string
is in the list of the variables. If not, it abort the attempt to change. Otherwise it creates a
string object with the correct space, which is the variable string size, added to the token size
without the variable. At the end, it replaces the variable with the correct string and updates
the original token string. Please note that the assignment requires only one exchange per
token, it then goes to find the next dollar sign.

\param tokenList
Token list to replace the variables with
\return
Boolean value to decide whether there is a invalid variable found in the string. 
Returning true means all valid. Otherwise,
Returning false means there is a invalid variable (abort the search).
*/
/************************************************************************/
bool uShell::replaceVars(TokenList &tokenList) const
{
	if (tokenList.empty())
	{
		return false;
	}
	// Remove comments
	for (size_t i = 0; i < tokenList.size(); i++)
	{
		if (tokenList[i].front() == '#')
		{
			tokenList.erase(tokenList.begin() + i, tokenList.end());
			break;
		}

		size_t start_Pos, end_Pos;

		// Check for ${
		start_Pos = tokenList[i].rfind("${");
		if (start_Pos != std::string::npos)
		{
			// Check for }
			end_Pos = tokenList[i].find_first_of('}', start_Pos);
			if (end_Pos != std::string::npos)
			{
				std::string key_ToReplace = tokenList[i].substr(start_Pos + 2, end_Pos - (start_Pos + 2));
				//check if potential key is valid
				if (isValidVarname(&key_ToReplace.front(), &key_ToReplace.back()))
				{
					std::string new_var{};
					key_ToReplace.erase(0, key_ToReplace.find_first_not_of(" \t\n\r\f\v"));
					//Find and replace
					if (m_vars.find(key_ToReplace) != m_vars.end() && !key_ToReplace.empty())
					{
						new_var = m_vars.find(key_ToReplace)->second;
						std::string new_Token = tokenList[i].substr(0, start_Pos);
						new_Token += new_var;
						new_Token += tokenList[i].substr(end_Pos + 1);
						tokenList[i] = new_Token;
					}
					else
					{
						std::cout << "Error: " << key_ToReplace << " is not a defined variable.\n";
						return false;
					}
				}
			}
		}
	}
	return true;
}
/************************************************************************/
/*!
\brief
Check whether each character is a number or digit from the given start and 
end of a character array.
It loops from start to end. In each iteration, it checks each digit if it’s a alphabert or
number.
\param start
Pointer to the start of string to search from
\param end
Pointer to the end of string where search stops
\return
boolean value to represent if the string is valid
Returning true means each character in the given string is valid. 
Otherwise, it returns false.
*/
/************************************************************************/
bool uShell::isValidVarname(char const *start, char const *end) const
{
	char *temp = const_cast<char *>(start);
	while (temp != end)
	{
		if (!isalpha(*temp) && !isdigit(*temp))
		{
			return false;
		}
		temp++;
	}

	return true;
}
/************************************************************************/
/*!
\brief
Merge all the tokens from a given token list, separated by a space, into one 
single string. We expect return value optimization and move scemantics help.
It loops from start to end. In each iteration, it checks each digit if it’s a alphabert or
number.
\param tokenList
The token list to take from
\param startPos
The starting position/index to start merging from 
\return
The merged string
*/
/************************************************************************/
std::string uShell::mergeTokens(TokenList const &tokenList, unsigned startPos) const
{
	std::string Word;
	//Merge all into one string
	for (unsigned i = startPos; i < tokenList.size(); i++)
	{
		Word += tokenList[i];
	}
	return Word;
}
/************************************************************************/
/*!
\brief
Echo the user input
This function prints all the tokens except the first, adding a space in between each pair of
token.
\param tokenList
The list of data to read in
*/
/************************************************************************/
void uShell::echo(TokenList const &tokenList)
{

	TokenList temp = tokenList;
	std::vector<std::string>::iterator v_it;
	//Print out token content
	for (size_t i = 1; tokenList.begin() + i != tokenList.end(); ++i)
	{
		if (i > 1)
		{
			std::cout << ' ';
		}
		std::cout << tokenList[i];
	}
	std::cout << std::endl;
}
/************************************************************************/
/*! 
\brief
In this function, if there is no input, then setvar command just returns. Otherwise it has
to check if the variable name is proper by ensuring that the first letter is an alphabet and
also continue to loop through the rest of the characters of this variable to check whether
the variable name is valid by using isValidVarname(). If there are more variables at the
back, it merges them all together (using mergeTokens()) and sets it to the mapped variable.
Otherwise, it just initializes to an empty string.
\param tokenList
The list of tokens to get the data value from
*/
/************************************************************************/
void uShell::setVar(TokenList const &tokenList)
{
	//check if tokenlist size is acceptable
	if (tokenList.size() >= 3)
	{
		std::string var_Merge = mergeTokens(tokenList, 2);
		//Assign map
		if (isValidVarname(tokenList[1].c_str(), tokenList[1].c_str() + tokenList[1].length()))
		{
			m_vars[tokenList[1]] = var_Merge;
		}
	}
	if (tokenList.size() < 3)
	{
		m_vars[tokenList[1]] = "";
	}
	else
	{
		return;
	}
}
/************************************************************************/
/*!
\brief
Public function for external call. Execute in loops and waits for input. 
It sets function pointers for echo and setvar in m internalCmdList. It sets PATH into the map in m vars.
\return
Exit code, of the exit command
*/
/************************************************************************/
int uShell::run()
{
	while (!m_exit)
	{
		std::cout << m_prompt << '>';
		std::string user_Input;
		getline(std::cin, user_Input, '\n');

		if (!getInput(user_Input))
		{
			m_exit = true;
			break;
		}

		TokenList tok_List;
		tokenize(user_Input, tok_List);

		if (m_verbose)
		{
			printVerbose(user_Input);
		}
		if (!replaceVars(tok_List))
		{
			continue;
		}
		if (tok_List.empty())
		{
			continue; // Continue to the next iteration
		}
		//Check all the checks
		if (tok_List[0] == "echo" && tok_List.size() > 1) 
		{
            echo(tok_List);
        }
        if (tok_List[0] == "setvar") 
		{           
            setVar(tok_List);
        }
        if (tok_List[0] == "changeprompt") 
		{
            m_prompt = mergeTokens(tok_List, 1);
        }
        if (tok_List[0] == "exit") 
		{
            m_exit = true;
            
            if(tok_List.size() > 1) 
			{
                m_exitCode = 1;
            }
            else 
			{
                m_exitCode = 0;
                continue;
            }
        }
	}
	return m_exitCode;
}
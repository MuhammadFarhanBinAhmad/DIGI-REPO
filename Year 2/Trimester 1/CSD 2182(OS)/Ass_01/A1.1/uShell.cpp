#include "uShell.h"
#include <iostream>
#include <functional>
#include <sstream>
using EchoFunction = void (*)(const std::string &);

uShell::uShell(bool bFlag) : m_verbose(bFlag), m_exit(false), m_exitCode(0)
{
	// Function pointer for the internal command
	m_internalCmdList["echo"] = &uShell::echo;
	m_internalCmdList["setvar"] = &uShell::setVar;

	m_prompt = "uShell";
}

bool uShell::getInput(std::string &input) const
{
	std::string temp_str = input;

	if (input.empty())
	{
		return false;
	}
	if (temp_str.back() == '\r')
	{
		temp_str[temp_str.size() - 1] = '\0';
	}

	return true;
}

void uShell::printVerbose(std::string const &input)
{

	int first = input.find_first_not_of(" \t\n\r\f\v");
	int last = input.find_last_not_of(" \t\n\r\f\v");

	std::cout << input.substr(first, last + 1)  << std::endl;
}

void uShell::tokenize(std::string const &input, TokenList &tokenList) const // works
{
	std::string word;
	std::stringstream iss(input);

	while (iss >> word)
	{
		tokenList.push_back(word);
	}

}

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

		//Check for ${
		start_Pos = tokenList[i].rfind("${");
		if (start_Pos != std::string::npos)
		{
			//Check for }
			//std::cout <<"end";
			end_Pos = tokenList[i].find_first_of('}',start_Pos);
			if (end_Pos != std::string::npos)
			{
				std::string key_ToReplace = tokenList[i].substr(start_Pos+2,end_Pos - (start_Pos + 2));

				if (isValidVarname(&key_ToReplace.front(),&key_ToReplace.back()))
				{
					std::string new_var{};
					key_ToReplace.erase(0, key_ToReplace.find_first_not_of(" \t\n\r\f\v"));

					if(m_vars.find(key_ToReplace)!= m_vars.end() && !key_ToReplace.empty())
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

std::string uShell::mergeTokens(TokenList const &tokenList, unsigned startPos) const
{
	std::string Word;

	for (unsigned i = startPos; i < tokenList.size(); i++)
	{
		Word += tokenList[i];
	}
	return Word;
}

void uShell::echo(TokenList const &tokenList)
{

	TokenList temp = tokenList;
	std::vector<std::string>::iterator v_it;

	for (size_t i = 1; tokenList.begin()+i != tokenList.end();++i)
	{
		if (i >1)
		{
			std::cout << ' ';
		}
		std::cout << tokenList[i];
	}
	std::cout << std::endl;

}

void uShell::setVar(TokenList const &tokenList)
{
	//set key and value in m_var
	if (tokenList.empty())
	{
		return;
	}
	const char *key_start = tokenList[1].c_str();
	const char *key_end = tokenList[1].c_str() + tokenList[1].size();
	std::string key;
	std::string value;

	if (isValidVarname(key_start, key_end))
	{
		key = tokenList[1];
	}
	else
	{
		return;
	}
	
	for (size_t i = 2 ; i < tokenList.size()-1; i++)
	{
		const char *value_start = tokenList[i].c_str();
		const char *value_end = tokenList[i].c_str() + tokenList[i].size();
		if (isValidVarname(value_start, value_end))
		{
			value += tokenList[i] + ' ';
		}
		else
		{
			return;
		}
	}
	value += tokenList[tokenList.size()-1];
	std::map<std::string,std::string>::iterator it;
	it = m_vars.find(key);
	if (it != m_vars.end())
	{
		it->second = value;
	}
	else
	{
		m_vars[key] = value;
	}
  }

int uShell::run()
{
	while (!m_exit)
	{
		std::cout << m_prompt << '>';
		
		std::string user_Input;
		getline(std::cin, user_Input);
		
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


		auto iter = m_internalCmdList.find(tok_List[0]);

		if (iter != m_internalCmdList.end())
		{
			(this->*(iter->second))(tok_List);
		}
	}
	return m_exitCode;
}
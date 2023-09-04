#include "uShell.h"
#include <iostream>
#include <functional>

using EchoFunction = void (*)(const std::string&);
using EchoFunction = void (*)(const std::string&);

uShell::uShell(bool bFlag): m_verbose(bFlag), m_exit(false), m_exitCode(0) 
{
	//Function pointer for the internal command
	m_internalCmdList["echo"] = &uShell::echo;
	m_internalCmdList["setvar"] = &uShell::setVar;

}

bool uShell::getInput(std::string& input) const
{
	std::string temp_str = input;
	if (temp_str.back() == '\r')
	{
		temp_str[temp_str.size() - 1] = '\n';
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
	
	for (std::string t : tokenList)
	{
		size_t pos = 0;

		while((pos = t.find('$',pos)) != std::string::npos)
		{
			if (pos + 1 < t.length() && t[pos+1] == '{')
			{
				//Find the closing }
				size_t end_pos = t.find('}',pos+1);
				if (end_pos != std::string::npos)
				{
					//Need to extract the content betwen the "${}"
					std::string var_Name = t.substr(pos +2 ,end_pos - pos - 2);

					//Check if variable name is valid
					if(isValidVarname(var_Name.c_str(),var_Name.c_str() + var_Name.length()))
					{
						auto var_it = m_vars.find(var_Name);
						if (var_it != m_vars.end())
						{
							t.replace(pos,end_pos-pos + 1,var_it->second);
						}
					}
					else
					{
						//Invalid variable name
						return false;
					}
				}
				else
				{
					//Fail to find '}'
					return false;
				}
			}
			//Move to next '$'
			pos++;
		}
	}
	return true;
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
	if (tokenList.size() < 2)
	{
		std::cout << "not enough var\n";
		return;
	}

	std::string var_Name = tokenList[1];

	if (!isalpha(var_Name[0]))
	{
		std::cout << "Invalid varible name: " << var_Name << std::endl;
		return;
	}

	std::string var_Value = "";

	if (tokenList.size() > 2 )
	{
		var_Value = mergeTokens(tokenList,2);
	}

	m_vars[var_Name] = var_Value;
}

int uShell::run()
{
	while(!m_exit)
	{
		std::cout << m_prompt;

		std::string user_Input;
		if (!getInput(user_Input))
		{
			break;
		}

		TokenList tok_List;
		tokenize(user_Input,tok_List);

		if (tok_List.empty())
		{
			continue;//Continue to the next iteration
		}

		auto iter = m_internalCmdList.find(tok_List[0]);
		
		if(iter != m_internalCmdList.end())
		{
			(this->*(iter->second))(tok_List);
		}
		else
		{
			std::cout << "Unknow Command: " << tok_List[0] << std::endl;
		}

	}
	return m_exitCode;
}
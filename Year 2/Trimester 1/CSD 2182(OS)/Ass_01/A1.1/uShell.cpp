#include "uShell.h"
#include <iostream>
#include <functional>

using EchoFunction = void (*)(const std::string&);

uShell::uShell(bool bFlag): m_verbose(bFlag), m_exit(false), m_exitCode(0)
{
	//Function pointer for the internal command
	m_internalCmdList["echo"] = &uShell::echo;
	m_internalCmdList["setvar"] = &uShell::setVar;

	m_prompt = "uShell";
}

bool uShell::getInput(std::string& input) const
{
	std::cout << input << std::endl;
	std::string temp_str = input;
	
	if (temp_str.find_first_of("exit"))
	{
		return false;
	}
	if (temp_str.find_first_not_of(" ") == std::string::npos)
	{
		return false;
	}
	if (temp_str.empty())
	{
		return false;
	}

	if (temp_str.back() == '\r')
	{
		temp_str[temp_str.size() - 1] = '\0';
	}

	return true;
}


void uShell::printVerbose(std::string const& input)
{
	int first = input.find_first_not_of("\t\n\r\f\v");
	int last = input.find_last_not_of("\t\n\r\f\v");

	std::cout << input.substr(first,last-first-1) << std::endl;
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

	std::vector<std::string>::iterator v_it;


	if (tokenList.empty())
	{
		return false;
	}


	//Remove comments
	for (v_it = tokenList.begin(); v_it!= tokenList.end();v_it++)
	{
		if ((*v_it).front() == '#')
		{
			tokenList.erase(v_it,tokenList.end());
			break;
		}
		if ((*v_it).rfind("${"))
		{
			int startpos = (*v_it).rfind("${");
			if ((*v_it).find('}'))
			{
				int endpos = (*v_it).find('}');
				std::string replace_str;
				replace_str = (*v_it).substr(startpos+2,endpos-(startpos+2));
				if (!replace_str.empty())
				{
					const char* temp_start = replace_str.c_str();
					const char* temp_end = replace_str.c_str() + replace_str.size();

					if (isValidVarname(temp_start,temp_end))
					{
						if (m_vars.count(replace_str))
						{
							replace_str = m_vars.at(replace_str);
							(*v_it).replace(startpos,endpos,replace_str);
							break;
						}
						else
						{
							std::cout << "Error: " << replace_str << " not a defined variable.\n";
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}


bool uShell::isValidVarname(char const* start, char const* end) const
{
	char* temp = const_cast<char*>(start);
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
	TokenList temp = tokenList;
	std::vector<std::string>::iterator v_it;

	for (v_it = temp.begin() + 1; v_it!= temp.end();v_it++)
	{
		std::cout << *v_it << ' ';
	}
	std::cout << "\n";
}

void uShell::setVar(TokenList const& tokenList)
{
	if (tokenList.empty())
	{
		return;
	}
	const char* temp_start = tokenList[0].c_str();
	const char* temp_end = tokenList[0].c_str() + tokenList[0].size();
	std::string key;
	std::string value;

	if (!isValidVarname(temp_start,temp_end))
	{
		key = tokenList[0];
	}
	else
	{
		return;
	}

	TokenList temp = tokenList;
	std::vector<std::string>::iterator str_it;

	for(str_it = temp.begin()+1; str_it != temp.end();str_it++)
	{
		value += *str_it;
	}

	m_vars[key] = value;

}

int uShell::run()
{
	while(!m_exit)
	{
		std::cout << m_prompt << '>';
		std::string user_Input;
		std::cin >> user_Input;

		if (!getInput(user_Input))
		{
			m_exit = true;
			break;
		}


		TokenList tok_List;
		tokenize(user_Input,tok_List);//

		if (tok_List.empty())
		{
			continue;//Continue to the next iteration
		}
		
		if (m_verbose)
		{
			printVerbose(user_Input);
		}

		if (!replaceVars(tok_List))
		{
			continue;
		}

		auto iter = m_internalCmdList.find(tok_List[0]);
		
		if(iter != m_internalCmdList.end())
		{
			(this->*(iter->second))(tok_List);
		}
	}
	return m_exitCode;
}
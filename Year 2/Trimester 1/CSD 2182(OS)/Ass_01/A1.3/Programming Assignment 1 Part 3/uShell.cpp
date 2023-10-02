#include "uShell.h"
#include <iostream>
#include <sstream>
#include <filesystem>

bool uShell::getInput(std::string &input)const
{
    
    if(!std::getline(std::cin, input))
    {
        return false;
    }
    if(input.back() == '\r')
    {
        input.erase(input.end()-1);
    }
    return true;
}

void uShell::printVerbose(std::string const& input)
{
    size_t start = input.find_first_not_of(' ');
    size_t end = input.find_last_not_of(' ');

    std::cout << input.substr(start,end -start + 1) << '\n';
}

void uShell::tokenize(std::string const& input, TokenList &tokenList)const
{
    std::istringstream iss(input);
    std::string words;

    while(iss >> words)
    {
        tokenList.push_back(words);
    }

}

bool uShell::replaceVars(TokenList &tokenList)const
{
    for(std::vector<std::string>::iterator str = tokenList.begin(); str != tokenList.end(); ++str)
    {
        if((*str)[0] == '#')
        {
            tokenList.erase(str,tokenList.end());
            return true;
        }

        size_t startPos = str->find("${");
        size_t endPos = str->find('}', startPos + 1);
        bool isValid = false;
        while(startPos != std::string::npos && endPos != std::string::npos)
        {
            std::string varName = (*str).substr(startPos +2, endPos - (startPos + 2));

            char firstch{*(varName.c_str())};
            if(varName.empty()||!(isalpha(firstch)))
            {
                startPos = str->find("${",startPos + 2);
                endPos = str->find("}", startPos);
                continue;
            }
            isValid = isValidVarname(varName.c_str(), varName.c_str()+ varName.length());
            if(isValid && m_vars.find(varName) != m_vars.end())
            {
                (*str) = (*str).substr(0,startPos) + m_vars.at(varName) + (*str).substr(endPos+1,(*str).length() - endPos);
            }
            else
            {
                
                if(isValid)
                {
                    if(m_vars.find(varName) == m_vars.end())
                    {
                        std::cerr << "Error: " << varName << " is not a defined variable.\n";
                        return false;
                    }

                }


                startPos = str->find("${", startPos +2);
                endPos = str->find("}", startPos);
            }
            startPos = str->find("${", startPos +m_vars.at(varName).length());
            endPos = str->find("}", startPos);
        }
    }
    return true;
}

bool uShell::isValidVarname(char const* start, char const* end)const
{
    char const* temp = start;
    while(temp != end)
    {
        char x = *temp;
        if(x < 'a' && x > 'z' && x < '0' && x > '9' && x < 'A' && x > 'Z')
        {
            return false;
        }
        temp++;
    }
    return true;
}

std::string uShell::mergeTokens(TokenList const& tokenList, unsigned startPos)const 
{
    std::stringstream ss;
    for(size_t i = startPos; i < tokenList.size(); i++)
    {
        ss << tokenList[i];
        if(i != (tokenList.size() -1))
        {
            ss << ' ';
        } 
    }
    return ss.str();
}

void uShell::echo(TokenList const& TokenList)
{
    std::string merged = mergeTokens(TokenList, 1);
    if(merged.length() != 0)
    std::cout << merged << '\n';
}

void uShell::setVar(TokenList const & tokenList)
{

    if(tokenList.size() <= 1)return;
    
    char firstchar{*(*(tokenList.begin()+1)).c_str()};

    if(!isalpha(firstchar))return;

    if(!isValidVarname((*(tokenList.begin()+1)).c_str(),
    (*(tokenList.begin()+1)).c_str()+(*(tokenList.begin()+1)).length()))return;

    std::string varName = *(tokenList.begin()+1);
    std::string varData{};

    if(tokenList.size() > 2)
    {
        varData = mergeTokens(tokenList,2);
    }
    m_vars[varName] = varData;
}

uShell::uShell(bool bFlag)
{
    m_verbose = bFlag;
    m_prompt = "uShell";
    m_internalCmdList["echo"]= &uShell::echo;
    m_internalCmdList["setvar"] = &uShell::setVar;
    m_vars["PATH"] = "";
}

int uShell::run()
{
    while(m_exit == false)
    {
        std::cout << m_prompt << ">";
        std::string input;
        if(!getInput(input))
        {
           m_exit = true;
        }

        if(input.empty())
        {
            continue;
        }

        TokenList buffer;
        tokenize(input,buffer);

        if(m_verbose)
        {
            printVerbose(input);
        }

        if(!replaceVars(buffer))
        {
            continue;
        }
        if(buffer.empty())
        {
            continue;
        }
        if(m_internalCmdList.find(buffer.front())!= m_internalCmdList.end())
        {
            (this->*m_internalCmdList[buffer.front()])(buffer);
        }
    }
    return m_exitCode;
}


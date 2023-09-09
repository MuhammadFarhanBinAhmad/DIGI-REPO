/*!************************************************************************
\file   uShell.hpp
\author Teo Teng Wee Shannon
\par    DP email: teo.t@digipen.edu
\par    Course: CSD 1171
\par    Operating Systems
\date   04-09-2023

\brief
    This source file makes a uShell that allows users to setvar, echo and
    replace var.

  The functions includes:
    - getInput
        Get one line of input from std::cin.
    
    - void printVerbose
        Print the user input without printing the starting and the trailing spaces.

    - void tokenize
        Tokenize the input	string	into a list of strings which are separated by spaces.

    - bool replaceVars
        Search and replace from the map all	variables in the token list with the value.

    - bool isValidVarname
        Check whether each character is a number or digit from the given start and end of a character array
    
    - std::string uShell::mergeTokens
        Merge all the tokens from a given token list, separated by a space, into one single string. 
        We expect return value optimization and move scemantics help . 
    
    - void echo
        Echo the user input

    - void setVar
        Set the value of a variable

    - uShell(bool bFlag)
        Creates the	class object of	uShell non default constructor for uShell

    - int run
        Public function	for	external call. Execute in loops and waits for input.
**************************************************************************/
#include "uShell.h"
#include <iostream>
#include <sstream>

/************************************************************************/
/*!
\brief
    Get one line of input from std::cin. Removes the trailing \r if any
\param input
    The input string to take the user input by reference
\return
    return false if encountering the EOF
*/
/************************************************************************/
bool uShell::getInput(std::string& input) const {

    if (!std::getline(std::cin, input, '\n')) {

        return false;
    }

    if(!input.empty()) {
        for (int i{}; input[i] != '\0'; ++i) {
                
            if (input[i] == '\r') {
                
                input.erase(i, 1);
            }
        }
    }
    return true;
}

/************************************************************************/
/*!
\brief
    Print the user input without printing the starting and the trailing spaces.
\param input
    The input string
*/
/************************************************************************/
void uShell::printVerbose(std::string const& input) {
    
    std::string newInput;
    
    size_t startingPos = input.find_first_not_of(" \t");
    size_t endingPos = input.find_last_not_of(" \t");
    
    if (startingPos != std::string::npos || endingPos != std::string::npos) {

        newInput = input.substr(startingPos, endingPos - startingPos + 1);

        std::cout << newInput << std::endl;
    }
}

/************************************************************************/
/*!
\ brief
    Tokenize the input string into a list of strings which are separated by
    spaces.
\param input
    The input string given by the user
\param token List
    Token list to fill up ,passed by reference to add strings to it
*/
/************************************************************************/
void uShell::tokenize(std::string const& input, TokenList& tokenList) const {
    
    std::istringstream iss(input);
    
    std::string token;
    
    while (iss >> token) {
        
        tokenList.push_back(token);
    }
}

/************************************************************************/
/*!
\ brief
    Search and replace from the map all variables in the token list with the value
\ param token List
    Token list to replace the variables with
\ return
    Boolean value to decide whether there is a invalid variable found in the string .
    Returning true means all valid. Otherwise,
    Returning false means there is an invalid variable (abort the search).
*/
/************************************************************************/
bool uShell::replaceVars(TokenList& tokenList) const {
    
    //remove all the tokens after the #
    for (int i {}; tokenList.begin() + i != tokenList.end(); ++i) {
        
        if (tokenList[i] == "#") {
            
            tokenList.erase(tokenList.begin() + i, tokenList.end());
            break;
        }
    }

    for (size_t i{}; tokenList.begin() + i != tokenList.end(); ++i) {
        
        //finds if its in the string
        size_t dollarCurlyIdx = tokenList[i].find_last_of("$");
        size_t scurlyIdx = tokenList[i].find_last_of("{");
        size_t ecurlyIdx = tokenList[i].find_first_of("}");

        //checks for signs
        if (dollarCurlyIdx != std::string::npos && ecurlyIdx != std::string::npos && (scurlyIdx == dollarCurlyIdx + 1)) {

            std::string varName = tokenList[i].substr(scurlyIdx + 1, ecurlyIdx - scurlyIdx - 1);

            bool isValid = isValidVarname(varName.c_str(), varName.c_str() + varName.length());
            
            if (isValid) {
                    
                if (m_vars.find(varName) != m_vars.end()) {
                    
                    tokenList[i].replace(dollarCurlyIdx, ecurlyIdx - dollarCurlyIdx + 1, m_vars.find(varName)->second);
                }
                else { 
                    
                    std::cout << "Error: " << varName << " is not a defined variable." << std::endl; 
                    return false;
                }
            }
            else { 

                continue;
            }
        }

    }
    return true;
}

/************************************************************************/
/*!
\ brief
    Check whether each character is a number or digit from the given start and
    end of a character array.
\ param start
    Pointer to the start of string to search from
\ param end
    Pointer to the end of string where search stops
\ return
    boolean value to represent if the string is valid
    Returning true means each character in the given string is valid.
    Otherwise, it returns false.
*/
/************************************************************************/
bool uShell::isValidVarname(char const* start, char const* end) const {
    
    for (int i{}; start + i != end; ++i) {
        
        if (isalpha(*(start + i)) || isdigit(*(start + i))) {

            continue;
        }
        else {

            return false;
        }
    }
    return true;
}

/************************************************************************/
/*!
\ brief
    Merge all the tokens from a given token list, separated by a space, into one
    single string. We expect return value optimization and move scemantics help.
\param tokenList
    The token list to take from
\param startPos
    The starting position / index to start merging from
\ return
    The merged string
*/
/************************************************************************/
std::string uShell::mergeTokens(TokenList const& tokenList, unsigned startPos) const {
    
    std::string str {};
    
    for (int i {}; tokenList.begin() + startPos + i  != tokenList.end(); ++i) {
        
        str += tokenList[startPos + i];
    }
    
    return str;
}

/************************************************************************/
/*!
\ brief
    Echo the userr input
\param tokenList
    The list of data to read in
*/
/************************************************************************/
void uShell::echo(TokenList const& tokenList) {
    
    for (int i {1}; tokenList.begin() + i != tokenList.end(); ++i) {
    
        if (i > 1) {

            std::cout << ' ';
        }
        std::cout << tokenList[i];
    }
    std::cout << std::endl;
}

/************************************************************************/
/*!
\ brief
    Set the value of a variable
\param tokenList
    The list of tokens to get the data value from
*/
/************************************************************************/
void uShell::setVar(TokenList const& tokenList) {
    
    if (tokenList.size() >= 3) {
        
        std::string mergeVar = mergeTokens(tokenList, 2);
        
        if (isValidVarname(tokenList[1].c_str(), tokenList[1].c_str() + tokenList[1].length())) {
            
            m_vars[tokenList[1]] = mergeVar;
        }
    }
    if (tokenList.size() < 3) {
        
        m_vars[tokenList[1]] = "";
    }
    else {

        return;
    }
}
 /************************************************************************/
/*!
\ brief
    Creates the class object of uShell
\param bFlag
    boolean value to decide whether to echo input
*/
/************************************************************************/
uShell::uShell(bool bFlag) {
    
    m_verbose = bFlag;
    m_exit = false; 
    m_exitCode = 0;
    m_prompt = "uShell";
    
    if (m_verbose) {
        
        m_internalCmdList["echo"] = &uShell::echo;
        m_internalCmdList["setvar"] = &uShell::setVar;
    }
}

/************************************************************************/
/*!
\ brief
    Public function for external call. Execute in loops and waits for input.
\ return
    Exit code, of the exit command
*/
/************************************************************************/
int uShell::run() {
    
    while (!m_exit) {
        
        std::cout << m_prompt << ">";
        
        std::string userInput{};

        bool inputFlag = getInput(userInput);
        
        if (!inputFlag) {
            
            m_exit = true;
            continue;
        }

        TokenList tokenList;
        tokenize(userInput, tokenList);
 
        if (m_verbose) {
            
            printVerbose(userInput);
        }

        if (!replaceVars(tokenList)) {
            
            continue;
        }
        if (tokenList.empty()) {
            
            continue;
        }
        if (tokenList[0] == "echo" && tokenList.size() > 1) {
            
            echo(tokenList);
        }
        if (tokenList[0] == "setvar") {
            
            setVar(tokenList);
        }
        if (tokenList[0] == "changeprompt") {
            
            m_prompt = mergeTokens(tokenList, 1);
        }
        if (tokenList[0] == "exit") {
            
            m_exit = true;
            
            if(tokenList.size() > 1) {
                
                m_exitCode = 1;
            }
            else {
                
                m_exitCode = 0;
                continue;
            }
        }
    }
    
    return m_exitCode;
}
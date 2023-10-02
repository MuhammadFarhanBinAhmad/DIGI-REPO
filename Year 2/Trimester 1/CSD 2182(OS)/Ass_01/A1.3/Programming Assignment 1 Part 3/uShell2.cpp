/*!************************************************************************
\file   uShell2.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\par    email: b.muhammadfarhan@digipen.edu
\par    Course: CSD 2182
\par    OS Part 1.2
\date   09-15-2023

\brief 	Create a basic shell program called uShell. A shell program behaves typically in a similar fashion to a command prompt.
        This is a continuation from part 1. Now we can changeprompt, exit the program upon command, and search for file
**************************************************************************/

#include "uShell2.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string> 

/************************************************************************/
/*!
\brief
Reads the exit code from the token list
If there is no other argument, it just returns 0. Otherwise, it parses the input into int and
returns.
\param tokenList
Stores the exit code that will be extracted
*/
/************************************************************************/
void uShell2::exit(TokenList const &tokenList)
{
    // Check token size
    if (tokenList.size() == 1)
    {
        m_exitCode = 0;
    }
    else
    {
        int temp = std::stoi(tokenList[1]);
        m_exitCode = temp;
    }
    m_exit = true;
}
/************************************************************************/
/*!
\brief
Changes the prompt that starts at every line
If changeprompt command is called but there is no input, the function just returns null
value. Otherwise, update prompt.



\param tokenList
The list of tokens where shell can retrieve the string value
*/
/************************************************************************/
void uShell2::changePrompt(TokenList const &tokenList)
{
    if (tokenList.size() > 1)
    {
        m_prompt = mergeTokens(tokenList, 1);
    }
}
/************************************************************************/
/*!
\brief
Sets up the argument lists required for calling the execvp function, and creates the child process
This function firstly checks whether the token3
list is an empty argument list. It simply returns if the list is empty. Otherwise it gets the merged command line arguments and
creates the argument array to put all the command line arguments. It then finds the
executable file name and checks if this is an absolute path either started with ‘/’ or ‘./’. If
so, it calls execvp() with the file name and the arguments. Else, it creates the environment
variables list (e.g. type of std :: vector < std :: string >). Please note that the function can
not be const because of the operator subscript of the map variable. It then loops through
the environment variables list, and tries to invoke the input file name if it exists. At the
end it deletes the created argument array. If no command has been found, it prints the
error message.
\param tokenList
The list of tokens to get the data value from
\param startParam
The starting token to parse data from the list
\param endParam
Pass the last token to parse data from the list
*/
/************************************************************************/
void uShell2::execute(TokenList const &tokenList, unsigned startParam, unsigned endParam)
{
    // Standard check
    if (tokenList.empty())
    {
        return;
    }

    char **args = new char *[endParam + 1];

    for (unsigned i = startParam; i < endParam; ++i)
    {
        args[i] = const_cast<char *>(tokenList[i].c_str());
    }

    char *command = const_cast<char *>(tokenList[0].c_str());

    args[endParam] = NULL;

    if (tokenList[0][0] != '/' || (tokenList[0][0] != '.' && tokenList[0][1] != '/'))
    {
        // Need check for "PATH" first else for some reason. I still dunno why this matter
        if (m_vars["PATH"] != getenv("PATH"))
        {
            std::cerr << "Error: " << command << " cannot be found\n";
            return;
        }

        if (execvp(command, args) == -1)
        {
            std::cerr << "Error: " << command << " cannot be found\n";
        }
    }
    else
    {
        std::string path = m_vars["PATH"];
        std::string temp{};

        std::vector<std::string> dir;

        for (int i = 0; path[i] != '\0'; ++i)
        {
            if (path[i] == ':')
            {
                dir.push_back(temp);
                temp.clear();
                continue;
            }

            temp += path[i];
        }

        bool itExist = false;

        if (tokenList[0][0] == '/')
        {

            if (execv(command, args) != 1)
            {
                itExist = true;
            }
        }
        else
        {
            for (std::string str : dir)
            {
                if (execvp(command, args) != 1)
                {
                    itExist = true;
                }
            }
        }
        if (itExist == false)
        {
            std::cerr << "Error: " << command << " cannot be found\n";
        }
    }
}
/************************************************************************/
/*!
\brief
Creates the class object of uShell2
It sets function pointers for changeprompt and exit in m internalCmdList2.

\param bFlag
Boolean value to decide whether to echo input
*/
/************************************************************************/
uShell2::uShell2(bool bFlag) : uShell(bFlag)
{
    // Set path and function pointer
    m_internalCmdList2["changeprompt"] = (fInternalCmd2)&uShell2::changePrompt;
    m_internalCmdList2["exit"] = (fInternalCmd2)&uShell2::exit;
    m_vars["PATH"] = getenv("PATH");

    m_exit = false;
    m_verbose = bFlag;
}
/************************************************************************/
/*!
\brief
Calls an external command using the passed parameters.
The function flushes the buffer and then uses fork() to spawn child process. Child process
will set the arguments to the input in the token list given to the process and call execute().
Then the child exits.The parent process should wait for the child to be done.


\param tokenList
The list of tokens to get the data value from
*/
/************************************************************************/
void uShell2::doExternalCmd(TokenList const &tokenList)
{
    std::cout.flush();
    pid_t status = fork();

    // Child is alive
    if (status == 0)
    {
        execute(tokenList, 0, tokenList.size());
        _exit(0);
    }
    // Child dead or exited
    else
    {
        int stat;
        wait(&stat);
    }
}
/************************************************************************/
/*!
\brief
Public function for external call. Execute in loops and waits for input.
This function is enhanced based on the assignment A1.1. It has a loop and firstly check
whether exit command is called. If so, it stops. Otherwise it prints out the prompt, with
the right arrow. Then it gets user input. If there are no more lines from the input, it exits
from the program (assume it gets re-directed input from the files). Otherwise, it clears the
input buffer for next input. Obviously, it needs to skip if there is no input (e.g. empty line).
It starts to tokenize the input otherwise. After this, it prints the input if verbose mode is
set. It replaces all variables if possible. If the function call for replacement replaceV ars()
returns false, an error has occurred, it continues to next line of input. Please note that
replacement also clears comments, so we have to check if the result is empty. Next, it
3
finds if it is an internal command in the first list m internalCmdList. If so, it activates
the internal command. Otherwise, it finds in the second list m internalCmdList2
and activates the internal command if there is a match. If the search for the
internal command fails, it regards the command as external command and does
the external command accordingly.4 Please note that if the next char is EOF, we
should end the loop to exit. Outside the loop, it returns exit code m exitCode.
“Tokens” are smaller chunks of the string that are separated by a specified character, called the delimiting
character.

\return
Exit code of the exit command
*/
/************************************************************************/
int uShell2::run()
{
    while (m_exit == false)
    {

        std::string user_Input;

        std::cout << m_prompt << ">";

        if (!getInput(user_Input))
        {
            m_exit = true;
        }

        if (user_Input.empty())
        {
            continue;
        }

        TokenList tok_List;
        tokenize(user_Input, tok_List);

        // Same check as before
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
            continue;
        }

        // Check all the internal command int the 2 list
        if (m_internalCmdList.find(tok_List.front()) != m_internalCmdList.end())
        {
            (this->*m_internalCmdList[tok_List.front()])(tok_List);
        }
        else if (m_internalCmdList2.find(tok_List.front()) != m_internalCmdList2.end())
        {
            (this->*m_internalCmdList2[tok_List.front()])(tok_List);
        }
        // if all fail means that trying to get file
        else
        {
            doExternalCmd(tok_List);
        }
    }
    return m_exitCode;
}